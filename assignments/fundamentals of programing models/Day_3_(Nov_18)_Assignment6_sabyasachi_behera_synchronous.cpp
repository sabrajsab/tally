#include <stdio.h>
#include <windows.h>

struct tNode {
    int     uData;
    tNode * uNext;
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

            printf ("queue empty in dequeue\n");
            return false;
        }
        tNode * newnode = nullptr;
        newnode = vHead;
        if (vHead == vTail) {

            vTail = nullptr;
        }
        vHead = vHead->uNext;
        printf ("dequeue happened, %d removed\n", newnode->uData);
        vLength--;
        free (newnode);
        return true;
    }
    void Display ()
    {
        if (vHead == nullptr) {

            printf ("queue empty in display\n");
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

DWORD WINAPI ThreadFunc (LPVOID pParam)
{
    tThreadParameter * param = (tThreadParameter *) pParam;
    while (param->uChoice == 0);
    switch (param->uChoice) {
    case 1:
        param->uObj->Enqueue(rand()%100);
        param->uIsFree = true;
        break;
    case 2:
        param->uObj->Dequeue();
        param->uIsFree = true;
        break;
    case 3:
        param->uObj->Display();
        param->uIsFree = true;
        break;
    case 4:
        param->uObj->DeleteQueue();
        param->uIsFree = true;
        break;
    case 5:
        param->uObj->NoOfNodes();
        param->uIsFree = true;
        break;
    }
}

int main ()
{
        Queue root;
        HANDLE threadhandle[45];
        int choice;

    for (int i = 0; i < 8; i++) {

        if (gParamArray[i].uIsCreated == false) {

            gParamArray[i].uIsCreated = true;
            gParamArray[i].uObj = &root;
            threadhandle[i] = CreateThread (NULL, 0, ThreadFunc, &gParamArray[i], NULL, NULL);
        }
    }

    // switch, 1-5 -> threadcall, 6-8 -> main thread related function, 9 -> exit

    /* 
    // synchronous 
    printf ("Enter:\n 1-Enqueue\n2-Dequeue\n3-Display\n4-DeleteQueue\n5-Length\6-createThread\n7-deleteThread\n8-poolInfo\n9-exit\n");
    scanf ("%d", &choice);
    */

    for (int j = 0; j < 100; ++j) {
        
        choice = (Rand() % 8) + 1;
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

                    printf ("\nno free threads !");
                    break;
                }
                gParamArray[first_free_thread].uChoice = choice;
                gParamArray[first_free_thread].uIsFree = false;
                break;
            case 6:
                for (int i = 0; i < 45; i++) {
                    if (gParamArray[i].uIsCreated == false) {

                        first_nothread = i;
                        break;
                    }
                }
                gParamArray [first_nothread].uIsCreated = true;
                gParamArray [first_nothread].uObj = &root;
                threadhandle [k] = CreateThread (NULL, 0, ThreadFunc, &gParamArray[first_nothread], NULL, NULL);
                break;
            case 7:
                if (first_free_thread == -1) {

                    printf ("\nno free threads !");
                    break;
                }
                if(TerminateThread(threadhandle[first_free_thread], 1)) {

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
                // exit, for synchronous
            default:
                printf ("wrong choice, enter again\n"); // for synchronous
        }
    }

    for (int i = 0; i < 45; ++i) {

        if (gParamArray[i].uIsCreated == true) {

            while (!gParamArray[i].uIsFree);
        }
        if(TerminateThread(threadhandle[first_free_thread], 1)) {

            gParamArray[first_free_thread].uIsCreated = false;
        }
    }

    /*
    SYSTEM_INFO sysinfo;
    GetSystemInfo (&sysinfo);
    int cores = sysinfo.dwNumberOfProcessors;
    printf ("%d\n", cores);
    */

    /*
    printf ("%d\n", root.NoOfNodes());
    root.Display();
    printf ("%d\n", root.Dequeue());
    printf ("%d\n", root.Enqueue(5));
    printf ("%d\n", root.Enqueue(8));
    printf ("%d\n", root.Enqueue(2));
    root.Display();
    printf ("%d\n", root.NoOfNodes());
    printf ("%d\n", root.Dequeue());
    root.Display();
    printf ("%d\n", root.NoOfNodes());
    root.DeleteQueue();
    root.Display();
    */
    return 0;
}

