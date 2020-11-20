#ifndef QUEUE_HPP
#define QUEUE_HPP


struct tNode {

    int     uData;
    tNode * uNext;
};


class Queue {

public:

    Queue            ();
    bool Enqueue     (int pValue);
    bool Dequeue     ();
    void Display     ();
    void DeleteQueue ();
    int  NoOfNodes   ();

private:

    tNode *vHead;
    tNode *vTail;
    int    vLength;
};

#include "queue.hxx"
#endif
