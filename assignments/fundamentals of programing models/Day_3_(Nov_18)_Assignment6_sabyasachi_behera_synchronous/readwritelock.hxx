#ifndef READWRITELOCK_HXX
#define READWRITELOCK_HXX

#include <stdio.h>
#include <windows.h>

#define threadcount 100


tLocks :: tLocks ()
{
    uReaders = 0;
    if ((uCounterMutex = CreateMutex(NULL, false, NULL)) == NULL) {

        printf ("error code: %d\n", GetLastError ());
    }

    if ((uReadWriteMutex = CreateMutex(NULL, false, NULL)) == NULL) {

        printf ("error code: %d\n", GetLastError ());
    }
}
tLocks uLockObj;

void ReadLock :: Wait ()
{
    flag = false;
    while (WaitForSingleObject (uLockObj.uCounterMutex, INFINITE) != WAIT_OBJECT_0);
    (uLockObj.uReaders)++;
    if (uLockObj.uReaders == 1) {

        flag = true;
        while (WaitForSingleObject (uLockObj.uReadWriteMutex, INFINITE) != WAIT_OBJECT_0) {}
    }
    if (!ReleaseMutex (uLockObj.uCounterMutex)) {

        printf ("error code: %d\n", GetLastError ());
    }
}
void ReadLock :: Signal ()
{
    while (WaitForSingleObject (uLockObj.uCounterMutex, INFINITE) != WAIT_OBJECT_0) {}
    (uLockObj.uReaders)--;
    if (!flag) {

        if (!ReleaseMutex (uLockObj.uCounterMutex)) {

            printf ("error code:%d\n", GetLastError ());
        }
        return;
    }
    while (uLockObj.uReaders != 0) {

        if (!ReleaseMutex (uLockObj.uCounterMutex)) {

            printf ("error code: %d\n", GetLastError ());
        }
        WaitForSingleObject (uLockObj.uCounterMutex, INFINITE);
    }

    if (!ReleaseMutex (uLockObj.uReadWriteMutex)) {

        printf ("error code: %d\n", GetLastError ());
    }
    if (!ReleaseMutex (uLockObj.uCounterMutex)) {

        printf ("error code: %d\n", GetLastError ());
    }
}
void WriteLock :: Wait ()
{
    while (WaitForSingleObject (uLockObj.uReadWriteMutex, INFINITE) != WAIT_OBJECT_0) {}
}
void WriteLock :: Signal ()
{
    if (!ReleaseMutex (uLockObj.uReadWriteMutex)) {

        printf ("in release mutex error code: %d\n", GetLastError ());
    }
}

#endif
