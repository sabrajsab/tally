#include <stdio.h>
#include <windows.h>

#define threadcount 100

struct tLocks
{
	int    * uReaders;
	int    * uTestvar;
	HANDLE * uCounterMutex;
	HANDLE * uReadWriteMutex;
};

class ReadLock {
    bool flag;
public:
    void Wait (tLocks * pObj) {
        flag = false;
        while (WaitForSingleObject (*(pObj -> uCounterMutex), INFINITE) != WAIT_OBJECT_0);
        (*(pObj -> uReaders))++;
        if ((*(pObj -> uReaders)) == 1) {

            flag = true;
            while (WaitForSingleObject ((*(pObj -> uReadWriteMutex)), INFINITE) != WAIT_OBJECT_0) {}
        }
        if (!ReleaseMutex ((*(pObj -> uCounterMutex)))) {

            printf ("error code: %d\n", GetLastError ());
        }
    }
    void Signal (tLocks * pObj) {
        while (WaitForSingleObject ((*(pObj -> uCounterMutex)), INFINITE) != WAIT_OBJECT_0) {}
        (*(pObj -> uReaders))--;
        if (!flag) {

            if (!ReleaseMutex ((*(pObj -> uCounterMutex)))) {

                printf ("error code:%d\n", GetLastError ());
            }
            return;
        }
        while ((*(pObj -> uReaders)) != 0) {

            if (!ReleaseMutex ((*(pObj -> uCounterMutex)))) {

                printf ("error code: %d\n", GetLastError ());
            }
            WaitForSingleObject ((*(pObj -> uCounterMutex)), INFINITE);
        }

        if (!ReleaseMutex ((*(pObj -> uReadWriteMutex)))) {

            printf ("error code: %d\n", GetLastError ());
        }
        if (!ReleaseMutex ((*(pObj -> uCounterMutex)))) {

            printf ("error code: %d\n", GetLastError ());
        }
    }
};

class WriteLock {
public:
    void Wait (tLocks * pObj) {
        while (WaitForSingleObject ((*(pObj -> uReadWriteMutex)), INFINITE) != WAIT_OBJECT_0) {}
    }
    void Signal (tLocks * pObj) {
        if (!ReleaseMutex ((*(pObj -> uReadWriteMutex)))) {

            printf ("in release mutex error code: %d\n", GetLastError ());
        }
    }
};

DWORD WINAPI FuncReadThread (LPVOID pParam)
{
	tLocks * obj = (tLocks *) pParam;
    ReadLock rl;
	rl.Wait (obj);
    printf ("%d ", *(obj -> uTestvar));
    rl.Signal(obj);
	return 0;
}

DWORD WINAPI FuncWriteThread (LPVOID pParam)
{
	tLocks * obj = (tLocks *) pParam;
    WriteLock wl;
	wl.Wait (obj);
    (*obj -> uTestvar)++;
    printf ("*%d ", *(obj -> uTestvar));
    wl.Signal (obj);
	return 0;
}

int main ()
{
		int    readers = 0;
		int    testvar  = 0;
		HANDLE counterMutex;
		HANDLE readWriteMutex;
        HANDLE threadhandles[threadcount];
        
    if ((counterMutex = CreateMutex(NULL, false, NULL)) == NULL) {

        printf ("error code: %d\n", GetLastError ());
        return 1;
    }

    if ((readWriteMutex = CreateMutex(NULL, false, NULL)) == NULL) {

        printf ("error code: %d\n", GetLastError ());
        return 1;
    }

    for (int i = 0; i < threadcount; i++) {
        
			tLocks obj;
			obj.uReaders = &readers;
			obj.uTestvar = &testvar;
			obj.uCounterMutex = &counterMutex;
			obj.uReadWriteMutex = &readWriteMutex;
		if (rand() % 2 == 0) {
			
            threadhandles[i] = CreateThread(NULL, 0, FuncWriteThread, &obj, NULL, NULL);
        } else {
			
            threadhandles[i] = CreateThread(NULL, 0, FuncReadThread, &obj, NULL, NULL);
        }
    }
    for (int i = 0; i < threadcount; i++) {

        if (WaitForSingleObject (threadhandles[i], INFINITE) != WAIT_OBJECT_0) {

            printf ("in here error code: %d\n", GetLastError ());
        }
    }

    for (int i = 0; i < threadcount; i++) {

        CloseHandle (threadhandles[i]);
    }
    CloseHandle (counterMutex);
    CloseHandle (readWriteMutex);
    return 0;
}

