#ifndef QUEUE_HXX
#define QUEUE_HXX
#include "readwritelock.hpp"

Queue :: Queue ()
{
    vHead = nullptr;
    vTail = nullptr;
    vLength = 0;
}

bool Queue :: Enqueue (int pValue)
{
    WriteLock wl;
    wl.Wait();
    printf("\nEnqueing %d\n", pValue);
    tNode * newnode = (tNode *) malloc (sizeof (tNode));
    if (newnode == nullptr) {

        wl.Signal();
        return false;
    }
    newnode->uData = pValue;
    newnode->uNext = nullptr;

    if (vHead == nullptr && vTail == nullptr) {

        vHead = vTail = newnode;
        vLength++;
        wl.Signal();
        return true;
    }
    vTail->uNext = newnode;
    vTail = newnode;
    vLength++;
    wl.Signal();
    return true;
}

bool Queue :: Dequeue ()
{
    WriteLock wl;
    wl.Wait();
    if (vHead == nullptr) {

        printf ("\nqueue empty in dequeue\n");
        wl.Signal();
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
    wl.Signal();
    return true;
}

void Queue :: Display ()
{
    ReadLock rl;
    rl.Wait();
    printf("\nDisplaying all elemnts of queue: ");
    if (vHead == nullptr) {

        printf ("\nqueue empty in display\n");
        rl.Signal();
        return;
    }
    tNode * temp = nullptr;
    temp = vHead;
    while (temp != nullptr) {

        printf ("%d ", temp->uData);
        temp = temp->uNext;
    }
    printf ("\n");
    rl.Signal();
}

void Queue :: DeleteQueue ()
{
    WriteLock wl;
    wl.Wait();
    while (true) {
        if (vHead == nullptr) {

            printf ("\nqueue empty in dequeue\n");
            break;
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
    }
    wl.Signal();
    return;
}

int Queue :: NoOfNodes ()
{
    ReadLock rl;
    rl.Wait ();
    return vLength;
    rl.Signal ();
}

#endif
