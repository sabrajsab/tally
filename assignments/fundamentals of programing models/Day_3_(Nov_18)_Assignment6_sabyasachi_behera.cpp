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
    while (param->uChoice == 0) {}

    param->uIsFree = false;
}

int main ()
{
        Queue root;
        HANDLE threadhandle[45];
        int choice;
        int j = 0;

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

    while (j < 100) {
        int i = 0;
        choice = (Rand() % 8) + 1;
        bool cancreate = false;
        bool selected = false;
        int k;
        int s = -1;

        // 1. search for free thread
        for (; i < 45; i++) {

            if (gParamArray[i].uIsFree == true && gParamArray[i].uIsCreated == true && selected == false) {

                selected = true;
                s = i;
            } else if (gParamArray[i].uIsCreated == false && cancreate == false) {

                cancreate = true;
                k = i;
            }
        }

        // 2. if no free thread, create new
        if (cancreate == true && s == -1) {

            gParamArray[k].uIsCreated = true;
            gParamArray[k].uObj = &root;
            threadhandle[k] = CreateThread (NULL, 0, ThreadFunc, &gParamArray[k], NULL, NULL);
            s = k;
            if (choice == 6) {

                continue;
            }
        }

        // 3. if max number of threads reached, wait for a thread to be free, or user will kill a thread
        if (cancreate == false && s == -1) {

            continue;
        }

        switch (choice) {
            case 1:
                gParamArray[s].uChoice = 1;
                gParamArray[s].uIsFree = false;
                break;
            case 2:
                gParamArray[s].uChoice = 2;
                gParamArray[s].uIsFree = false;
                break;
            case 3:
                gParamArray[s].uChoice = 3;
                gParamArray[s].uIsFree = false;
                break;
            case 4:
                gParamArray[s].uChoice = 4;
                gParamArray[s].uIsFree = false;
                break;
            case 5:
                gParamArray[s].uChoice = 5;
                gParamArray[s].uIsFree = false;
                break;
            case 6:
                
                break;
            case 7:
                // kill thread
                break;
            case 8:
                // pool info
                break;
            case 9:
                // exit, for synchronous
            default:
                printf ("wrong choice, enter again\n"); // for synchronous
        }
        j++;
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

