#ifndef LINKEDLIST_HXX
#define LINKEDLIST_HXX

node * CreateNewNode (int pObj) 
{
    node * ptr            = new node;
    ptr -> uObj           = pObj;
    ptr -> uNextDown      = nullptr;
    ptr -> uNextSide      = nullptr;
    return ptr;
}

node * & NextDown (node * pPtr)
{
    return pPtr -> uNextDown;
}

node * & NextSide (node * pPtr)
{
    return pPtr -> uNextSide;
}

void DisplayAll (node * pLlStart)
{
    while (pLlStart != nullptr) {

        printf ("%d ", pLlStart -> uObj);
        pLlStart = pLlStart -> uNextDown;
    }
}

void SortLinkedList (node * pPtr)
{
   
    node * pPtrDown = pPtr;
    while (pPtr -> uNextSide) {

        if (!(pPtrDown -> uNextDown)) {

            pPtrDown->uNextDown = pPtr->uNextSide;
            pPtr->uNextSide = pPtr->uNextSide->uNextSide;
            pPtrDown = pPtr;
            continue;
        }

        if ((pPtrDown -> uNextDown -> uObj) < (pPtr -> uNextSide -> uObj)) {

            pPtrDown = pPtrDown -> uNextDown;
        } else {

            pPtrDown -> uNextSide = pPtr -> uNextSide;
            pPtr -> uNextSide = pPtr -> uNextSide -> uNextDown;
            pPtrDown -> uNextSide -> uNextDown = pPtrDown -> uNextDown;
            pPtrDown -> uNextDown = pPtrDown -> uNextSide;
            if (pPtr -> uNextSide) {

                pPtr -> uNextSide-> uNextSide = pPtrDown -> uNextSide -> uNextSide;
            } else {

                pPtr -> uNextSide = pPtrDown -> uNextSide -> uNextSide;
                pPtrDown = pPtr;
                continue;
            }
            
            pPtrDown = pPtrDown -> uNextDown;
        }
        
    }
}

#endif
