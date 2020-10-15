#ifndef LINKEDLIST_HXX
#define LINKEDLIST_HXX

node * CreateNewNode (Person * pObj) 
{
    node * ptr            = new node;
    ptr -> uObj           = pObj;
    ptr -> uNext          = nullptr;
    ptr -> uNextPrincipal = nullptr;
    ptr -> uNextTeacher   = nullptr;
    ptr -> uNextDeveloper = nullptr;
    return ptr;
}

node * & NextPerson (node * pPtr)
{
    return pPtr -> uNext;
}

node * & NextPrincipal (node * pPtr)
{
    return pPtr -> uNextPrincipal;
}

node * & NextTeacher (node * pPtr)
{
    return pPtr -> uNextTeacher;
}

node * & NextDeveloper (node * pPtr)
{
    return pPtr -> uNextDeveloper;
}

void DisplayAll (node * pLlStart, node * & (*pFunPtr) (node *))
{
    while (pFunPtr(pLlStart) != nullptr) {

        pLlStart = pFunPtr (pLlStart);
        pLlStart -> uObj -> Display ();
    }
}

void Push (node * & pLlStart, node * & pNewNode, node * & (*pFunPtr) (node *))
{
        node * End         = pLlStart;
        node * SpecificEnd = pLlStart;
    while ((End -> uNext) != nullptr) {

        End = End -> uNext;
    }
    End -> uNext = pNewNode;

    while (pFunPtr (SpecificEnd) != nullptr) {

        SpecificEnd = pFunPtr (SpecificEnd);
    }
    pFunPtr (SpecificEnd) = pNewNode;
}

void BubbleSort (node * pPtr, node * & (*pFunPtr) (node *), bool (* CompareFunptr) (Person *, Person *))
{
   
        node * Ptr1 = pPtr;
        node * Ptr2 = pPtr;
        node * Ptr3 = pPtr;
        int    k    = 0;
        bool   flag {true};
        bool   CompareValue;
    while (pFunPtr(Ptr2) != nullptr) {

        k++;
        Ptr2 = pFunPtr (Ptr2);
    }
        
    for (; k > 1 && flag; --k) {

            int i;
        flag = false;
        for (i = 1, Ptr2 = pFunPtr(pPtr), Ptr3 = pPtr; i<k; Ptr3 = pFunPtr(Ptr3),++i) {

             CompareValue = CompareFunptr (Ptr2 -> uObj, pFunPtr (Ptr2) -> uObj);
             
             if (CompareValue) {

                 flag              = true;
                 node * SwapPtr    = pFunPtr (Ptr2);
                 pFunPtr (Ptr2)    = pFunPtr(SwapPtr);
                 pFunPtr (Ptr3)    = SwapPtr;
                 pFunPtr (SwapPtr) = Ptr2;
            }
            else {

                Ptr2 = pFunPtr (Ptr2);
            }
        }
    }
}

#endif
