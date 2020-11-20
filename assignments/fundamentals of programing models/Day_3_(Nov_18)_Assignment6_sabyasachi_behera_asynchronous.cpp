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
        printf("\nDisplaying all elemnts of queue: ");
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
            printf ("\nNo. of threads : %d", param->uObj->NoOfNodes());
            break;
        }
        param->uChoice = 0;
        param->uIsFree = true;
    }
    return 0;
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

    for (int j = 0; j < 100; ++j) {

        printf("\n********%d*********\n", j);
        
        choice = (rand() % 8) + 1;
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
                if (first_nothread == -1) {

                    printf("\nNo space left for new threads");
                    break;
                }
                gParamArray[first_nothread].uIsCreated = true;
                gParamArray [first_nothread].uObj = &root;
                threadhandle [first_nothread] = CreateThread (NULL, 0, ThreadFunc, &gParamArray[first_nothread], NULL, NULL);
                break;
            case 7:
                if (first_free_thread == -1) {

                    printf ("\nno free threads !");
                    break;
                }
                if(TerminateThread(threadhandle[first_free_thread], 1)) {

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
        }
    }

    for (int i = 0; i < 45; ++i) {

        if (gParamArray[i].uIsCreated == true) {

            while (!gParamArray[i].uIsFree);
            
            if(TerminateThread(threadhandle[i], 1)) {

                CloseHandle(threadhandle[i]);
                gParamArray[i].uIsCreated = false;
            }
        }
    }
    return 0;
}
