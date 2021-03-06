#include <stdio.h>
#include <windows.h>
#include "readwritelock.hpp"
#include "queue.hpp"
#include "customio.hpp"

struct tThreadParameter {
    tThreadParameter ()
    {
        uChoice = 0;
        uIsCreated = false;
        uIsFree = true;
        uObj = nullptr;
    }
    volatile int uChoice;
    Queue * uObj;
    volatile bool uIsFree;
    volatile bool uIsCreated;
} gParamArray[45];


DWORD WINAPI ThreadFunc (LPVOID pParam)
{
    tThreadParameter * param = (tThreadParameter *) pParam;
    while (true) {

        while (param->uChoice == 0) {

            if (!param->uIsCreated) {

                return 0;
            }
        }
        printf("\nthread execution starting, doing task %d\n", param->uChoice);
        switch (param->uChoice) {
        case 1:
            param->uObj->Enqueue(rand()%100);
            break;
        case 2:
            param->uObj->Dequeue();
            break;
        case 3:
            param->uObj->Display();
            break;
        case 4:
            param->uObj->DeleteQueue();
            break;
        case 5:
            printf ("\nNo. of nodes : %d\n", param->uObj->NoOfNodes());
            break;
        }
        param->uChoice = 0;
        param->uIsFree = true;
    }
}

int main ()
{
        Queue root;
        HANDLE threadhandle[45];
        volatile int choice;
    for (int i = 0; i < 8; i++) {

        gParamArray[i].uIsCreated = true;
        gParamArray[i].uObj = &root;
        threadhandle[i] = CreateThread (NULL, 0, ThreadFunc, &gParamArray[i], NULL, NULL);
    }

    printf ("1. Enqueue, 2. Dequeue, 3. Display all queue, 4. Empty whole queue, 5. show no. of nodes in queue\n\
                6. create new thread, 7. Delete a thread, 8. show threa pool, 9. exit\n");
    for (int j = 0; j < 100; ++j) {

        choice = scan <int> ();
        printf ("\n********%d %d*********\n", j, choice);
            int first_free_thread = -1;
            int first_nothread = -1;
            int no_of_free_threads = 0;
            int no_of_working_threads = 0;

        for (int i = 0; i < 45; i++) {

            if (gParamArray[i].uIsFree == true && gParamArray[i].uIsCreated == true) {

                first_free_thread = i;
                break;
            }
        }
        
        switch (choice) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                if (first_free_thread == -1) {

                    printf ("\nno free threads for choice : %d!\n", choice);
                    break;
                }
                printf("\nAssigning thread %d to do task %d\n", first_free_thread, choice);
                gParamArray[first_free_thread].uChoice = choice;
                gParamArray[first_free_thread].uIsFree = false;
                //while (gParamArray[first_free_thread].uChoice != 0);

                break;
            case 6:
                for (int i = 0; i < 45; i++) {
                    if (gParamArray[i].uIsCreated == false) {

                        first_nothread = i;
                        break;
                    }
                }
                if (first_nothread == -1) {

                    printf("\nNo space left for new threads\n");
                    break;
                }
                printf("\nCreating new threadj\n");
                gParamArray [first_nothread].uIsCreated = true;
                gParamArray [first_nothread].uObj = &root;
                threadhandle [first_nothread] = CreateThread (NULL, 0, ThreadFunc, &gParamArray[first_nothread], NULL, NULL);
                break;
            case 7:
                for (int i = 0; i < 45; i++) {

                    if (gParamArray[i].uIsCreated == true) {

                        if (gParamArray[i].uIsFree == true) {

                            no_of_free_threads++;
                        }
                    }
                }
                if (no_of_free_threads <= 1) {

                    printf ("\nOnly 1 thread remains.. Cant delete\n");
                    break;
                }
                printf ("\nDeleting thread : %d\n", first_free_thread);
                gParamArray [first_free_thread].uIsCreated = false;
                if (WaitForSingleObject (threadhandle [first_free_thread], INFINITE) != WAIT_OBJECT_0) {

                    printf ("error code: %d\n", GetLastError ());
                }
                CloseHandle(threadhandle[first_free_thread]);
                break;
            case 8:
                for (int i = 0; i < 45; i++) {

                    if (gParamArray[i].uIsCreated == true) {

                        if (gParamArray[i].uIsFree == true) {

                            no_of_free_threads++;
                        } else {

                            no_of_working_threads++;
                        }
                    }
                }
                printf("\nTotal no. of threads : %d, No. of free threads : %d\n", no_of_free_threads + no_of_working_threads, no_of_free_threads);
                break;
            case 9:
                for (int i = 0; i < 45; ++i) {

                    if (gParamArray[i].uIsCreated == true) {

                        while (!gParamArray[i].uIsFree);
                        
                        
                        gParamArray[i].uIsCreated = false;
                        if (WaitForSingleObject (threadhandle[i], INFINITE) != WAIT_OBJECT_0) {

                            printf ("error code: %d\n", GetLastError ());
                        }
                        CloseHandle(threadhandle[i]);
                    }
                }
                return 0;
            default:
                printf("\nInvalid choice\n");
        }
    }
    for (int i = 0; i < 45; ++i) {

        if (gParamArray[i].uIsCreated == true) {

            while (!gParamArray[i].uIsFree);
            
            
            gParamArray[i].uIsCreated = false;
            if (WaitForSingleObject (threadhandle[i], INFINITE) != WAIT_OBJECT_0) {

                printf ("error code: %d\n", GetLastError ());
            }
            CloseHandle(threadhandle[i]);
        }
    }
    return 0;
}
