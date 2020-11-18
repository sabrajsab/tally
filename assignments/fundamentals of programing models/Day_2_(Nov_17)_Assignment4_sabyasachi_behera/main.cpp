#include <stdio.h>
#include <Windows.h>
#include "customio.hpp"

struct tPrintInfo
{
	int * uLastTurn;
	int * uToken;
	int * uVal;
	int   uSignature;
	int * uMax;
};

int wait (tPrintInfo * tokenobj)
{
	while (true) {
		
		if (*(tokenobj -> uToken) == (tokenobj -> uSignature)) {
			
			return 0;
		}
	}
}

int signal (tPrintInfo * tokenobj)
{
	if ((*(tokenobj -> uToken)) != 0) {
		
		(*(tokenobj -> uToken)) = 0;
	} else {
		
		(*tokenobj -> uToken) = ((*tokenobj -> uLastTurn) == 1? 2 : 1);
		(*tokenobj -> uLastTurn) = (*tokenobj -> uToken);
	}
	return 0;
}

DWORD WINAPI ThreadPrint (LPVOID pParam)
{
	tPrintInfo * tokenobj = (tPrintInfo *) pParam;
	if(*(tokenobj -> uMax) < 2 && *(tokenobj -> uMax) > -2 && (tokenobj -> uSignature) == 2) {
		
		return 0;
	}
	if (*(tokenobj -> uMax) == 0) {
		
		return 0;
	}
	while (true)  {
	
		if (wait(tokenobj) != 0) {
			
			return 1;
		}
		
		if (tokenobj -> uSignature == 0) {
			
			printf ("0 ");
		} else {
			
			if (*(tokenobj -> uMax) < 0) {
				
				printf ("%d ", *(tokenobj -> uVal) + *(tokenobj -> uMax));
			} else {
				
				printf ("%d ", *(tokenobj -> uVal) + 1);
			}
			(*tokenobj -> uVal) ++;
		}
		if (*(tokenobj -> uVal) >= (((*(tokenobj -> uMax) > 0) ? 1 : -1) * (*(tokenobj -> uMax))) - 1) {
			
			if(signal(tokenobj) != 0){
			
				return 1;
			}
			break;
		}
		if(signal(tokenobj) != 0){
			
			return 1;
		}
	}
	//printf ("here %d", tokenobj -> uSignature);
	return 0;
}

int main(int pArgc, char ** pArgv)
{
		tPrintInfo obj [3];
		int printval = 0;
		int token = 0;
		int max;
		HANDLE thread_handle [3];
		bool b_wait_all = true;
		int return_val_WaitForMultipleObjects;
		int lastTurn = 0;
		
	if (pArgc == 1) {
		
		max = 10;
	} else {
		
		//printf ("*%d*", pArgv [1][1]);
		if (!CheckInt (pArgv[1], max)) {

			return 1;
		}
	}
	if (max > 184 || max < -100) {
		
		printf ("input should be in range [-100, 184]\n");
		return 1;
	}
	for (int i = 0; i < 3; ++i) {
		
		obj [i].uLastTurn      = &lastTurn;
		obj [i].uSignature     = i;
		obj [i].uToken    	   = &token;
		obj [i].uVal      	   = &printval;
		obj [i].uMax      	   = &max;
		thread_handle [i]      = CreateThread(NULL, 0, ThreadPrint, &obj[i], NULL, NULL);
		if (thread_handle [i] == 0) {
			
			printf ("\nThread Creation Failed. Exiting");
			return 2;
		}
	}

    return_val_WaitForMultipleObjects = WaitForMultipleObjects (3, thread_handle, b_wait_all, INFINITE);
	if (!b_wait_all || return_val_WaitForMultipleObjects < WAIT_OBJECT_0 || return_val_WaitForMultipleObjects > (WAIT_OBJECT_0 + 2)) {
			
		printf ("\nWaitForMultipleObjects failed");
		return 3;
		
	}
	for (int i = 0; i < 3; ++i) {
        
        
		if (!CloseHandle (thread_handle[i])) {
			
			printf ("cant close handle");
			return 4;
		}
    }
	return 0;
}