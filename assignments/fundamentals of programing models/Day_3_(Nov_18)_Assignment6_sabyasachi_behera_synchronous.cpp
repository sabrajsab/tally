#include <stdio.h>
#include <windows.h>

HANDLE gLock;

struct tNode {
    int     uData;
    tNode * uNext;
};

class Queue {
  public:
    Queue ()
    {
        vHead = nullptr;
        vTail = nullptr;
        vLength = 0;
    }
    bool Enqueue (int pValue)
    {
        printf("Enqueing %d", pValue);
        tNode * newnode = (tNode *) malloc (sizeof (tNode));
        if (newnode == nullptr) {

            return false;
        }
        newnode->uData = pValue;
        newnode->uNext = nullptr;

        if (vHead == nullptr && vTail == nullptr) {

            vHead = vTail = newnode;
            vLength++;
            return true;
        }
        vTail->uNext = newnode;
        vTail = newnode;
        vLength++;
        return true;
    }
    bool Dequeue ()
    {
        if (vHead == nullptr) {

            printf ("\nqueue empty in dequeue\n");
            return false;
        }
        tNode * newnode = nullptr;
        newnode = vHead;
        if (vHead == vTail) {

            vTail = nullptr;
        }
        vHead = vHead->uNext;
        printf ("\ndequeue happened, %d removed\n", newnode->uData);
        vLength--;
        free (newnode);
        return true;
    }
    void Display ()
    {
        printf("\nDisplaying all elemnts of queue: ");
        if (vHead == nullptr) {

            printf ("\nqueue empty in display\n");
            return;
        }
        tNode * temp = nullptr;
        temp = vHead;
        while (temp != nullptr) {

            printf ("%d ", temp->uData);
            temp = temp->uNext;
        }
        printf ("\n");
    }
    void DeleteQueue ()
    {
        printf ("\ndeletequeue");
        while (Dequeue());
    }
    int NoOfNodes ()
    {
        return vLength;
    }
  private:
    tNode * vHead;
    tNode * vTail;
    int     vLength;
};

struct tThreadParameter {
    tThreadParameter ()
    {
        uChoice = 0;
        uIsCreated = false;
        uIsFree = true;
    }
    int uChoice;
    Queue * uObj;
    bool uIsFree;
    bool uIsCreated;
} gParamArray[45];


DWORD WINAPI ThreadFunc (LPVOID pParam)
{

    tThreadParameter * param = (tThreadParameter *) pParam;
    while (true) {
        while (param->uChoice == 0);
        
        //while (WaitForSingleObject (gLock, INFINITE) != WAIT_OBJECT_0);
        printf ("\nchoice: %d", param->uChoice);
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
            printf ("\nNo. of nodes : %d", param->uObj->NoOfNodes());
            break;
        }
        
        /*if (!ReleaseMutex (gLock)) {

            printf ("error code: %d\n", GetLastError ());
        }*/
        
        param->uChoice = 0;
        param->uIsFree = true;
    }
}

int main ()
{
        Queue root;
        HANDLE threadhandle[45];
        int choice;

    if ((gLock = CreateMutex(NULL, false, NULL)) == NULL) {

        printf ("error code: %d\n", GetLastError ());
        return 1;
    }
    for (int i = 0; i < 8; i++) {

        if (gParamArray[i].uIsCreated == false) {

            gParamArray[i].uIsCreated = true;
            gParamArray[i].uObj = &root;
            threadhandle[i] = CreateThread (NULL, 0, ThreadFunc, &gParamArray[i], NULL, NULL);
        }
    }

    printf ("1. Enqueue, 2. Dequeue, 3. Display all queue, 4. Empty whole queue, 5. show no. of nodes in queue\n\
                6. create new thread, 7. Delete a thread, 8. show threa pool, 9. exit");
    for (int j = 0; j < 100; ++j) {

        choice = (rand() % 8) + 1;
        //scanf ("%d", &choice);
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

                    printf ("\nno free threads for choice : %d!", choice);
                    break;
                }
                gParamArray[first_free_thread].uChoice = choice;
                gParamArray[first_free_thread].uIsFree = false;
                while (gParamArray[first_free_thread].uChoice != 0);

                break;
            case 6:
                for (int i = 0; i < 45; i++) {
                    if (gParamArray[i].uIsCreated == false) {

                        first_nothread = i;
                        break;
                    }
                }
                if (first_nothread == -1) {

                    printf("\nNo space left for new threads");
                    break;
                }
                printf("\nCreating new thread");
                gParamArray [first_nothread].uIsCreated = true;
                gParamArray [first_nothread].uObj = &root;
                threadhandle [first_nothread] = CreateThread (NULL, 0, ThreadFunc, &gParamArray[first_nothread], NULL, NULL);
                //printf ("*%d*", first_nothread);
                break;
            case 7:
                if (first_free_thread == -1) {

                    printf ("\nno free threads to delete!");
                    break;
                }
                if(TerminateThread(threadhandle[first_free_thread], 1)) {

                    printf("\nDeleting thread : %d", first_free_thread);
                    CloseHandle(threadhandle[first_free_thread]);
                    gParamArray[first_free_thread].uIsCreated = false;
                }

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
                printf("\nTotal no. of threads : %d, No. of free threads : %d", no_of_free_threads + no_of_working_threads, no_of_free_threads);
                break;
            case 9:
                for (int i = 0; i < 45; ++i) {

                    if (gParamArray[i].uIsCreated == true) {

                        while (!gParamArray[i].uIsFree);
                        
                        if (TerminateThread (threadhandle[i], 1)) {

                            CloseHandle(threadhandle[i]);
                            gParamArray[i].uIsCreated = false;
                        }
                    }
                }
                CloseHandle (gLock);
                printf("\nabout to exit 1");
                return 0;
        }
    }
    //printf("\nabout to exit 2");
    for (int i = 0; i < 45; ++i) {

        if (gParamArray[i].uIsCreated == true) {

            //printf ("#%d#", i);
            while (!gParamArray[i].uIsFree);
            //printf ("#%d#", i);
            if (TerminateThread (threadhandle[i], 1)) {

                printf ("%d", i);
                CloseHandle (threadhandle[i]);
                gParamArray[i].uIsCreated = false;
            }
        }
    }
    CloseHandle (gLock);
    printf("\nabout to exit 2");
    return 0;
}
