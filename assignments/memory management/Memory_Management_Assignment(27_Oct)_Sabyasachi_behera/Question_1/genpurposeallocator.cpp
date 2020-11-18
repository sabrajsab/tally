#ifndef GENPURPOSEALLOCATOR_HXX
#define GENPURPOSEALLOCATOR_HXX

#include <stdio.h>
#include <Windows.h>
#include <stdint.h>
#include "genpurposeallocator.hpp"

const int       gcMaxSz = 57;
static Header * gFree;

void Free (void * pPtrToFree)
{
    Header * headerofmemtofree;
    Header * headerofnext;
    Header * headerofprev;

    headerofmemtofree = (Header *) pPtrToFree - 1;

    headerofnext = headerofmemtofree + (headerofmemtofree -> uBuff.uSize);

    headerofprev = headerofmemtofree - ((headerofmemtofree - 1) -> uBuff.uSize);

    if(headerofnext->uBuff.uFlag == true && headerofprev->uBuff.uFlag == true) {
        
        headerofprev->uBuff.uSize += (headerofmemtofree->uBuff.uSize + headerofnext->uBuff.uSize); //prev size
        (headerofnext+(headerofnext->uBuff.uSize))->uBuff.uSize = headerofprev->uBuff.uSize; // footer size
        if (headerofnext->uBuff.uPrevPtr) {
            (headerofnext->uBuff.uPrevPtr)->uBuff.uNextPtr = headerofnext->uBuff.uNextPtr; //next's prev's link
        }
        if (headerofnext->uBuff.uNextPtr) {

            (headerofnext->uBuff.uNextPtr)->uBuff.uPrevPtr = headerofnext->uBuff.uPrevPtr; //next's next's link
        }
    }

    else if (headerofnext -> uBuff.uFlag == true) {

        headerofmemtofree->uBuff.uSize += headerofnext->uBuff.uSize;  //current's size
        (headerofmemtofree + (headerofmemtofree->uBuff.uSize) - 1) -> uBuff.uSize = headerofmemtofree->uBuff.uSize; //footer's size

        headerofmemtofree->uBuff.uNextPtr = headerofnext->uBuff.uNextPtr; //current link next
        headerofmemtofree->uBuff.uPrevPtr = headerofnext->uBuff.uPrevPtr; //current link prev
        if (headerofnext->uBuff.uPrevPtr) {
            (headerofnext->uBuff.uPrevPtr)->uBuff.uNextPtr = headerofmemtofree; //next's prev's next pointer
        }
        if (headerofnext->uBuff.uNextPtr) {

            (headerofnext->uBuff.uNextPtr)->uBuff.uPrevPtr = headerofmemtofree; //next's next's prev pointer
        }
        headerofmemtofree->uBuff.uFlag = true;
        gFree = headerofmemtofree;
    } else if (headerofprev -> uBuff.uFlag == true) {

        headerofprev -> uBuff.uSize += headerofmemtofree -> uBuff.uSize; //prev's new size
        (headerofprev + (headerofprev -> uBuff.uSize) - 1) -> uBuff.uSize = headerofprev -> uBuff.uSize; //current footer's size
    } else {  //add this free block to the end of the linked list

        headerofmemtofree -> uBuff.uNextPtr = gFree;
        headerofmemtofree -> uBuff.uPrevPtr = nullptr;
        headerofmemtofree->uBuff.uFlag = true;
        gFree = headerofmemtofree;
    }
}

static Header * GetMemoryFromOS (unsigned pSize)
{
    char * bufffromos;
    Header * up;

    if (pSize < gcMaxSz) {

        pSize = gcMaxSz;
    }

    bufffromos = (char *) HeapAlloc (GetProcessHeap (), NULL, pSize * sizeof (Header));

    if (bufffromos == NULL) {

        return NULL;
    }

    up = (Header *) bufffromos;
    up->uBuff.uSize = pSize;
    up->uBuff.uPrevPtr = nullptr;
    up->uBuff.uNextPtr = gFree;
    up->uBuff.uFlag = true;
    gFree = up;
    //Free ((void *)(up + 1));

    (up + pSize - 1) -> uBuff.uSize = pSize;
    return gFree;
}

void * Malloc (unsigned pSize)
{
	Header * prev;
    uint32_t normalizedunits;

    normalizedunits = (pSize + sizeof (Header) - 1) / sizeof (Header) + 2;
    prev = nullptr;

    for (Header * curr = gFree; curr != nullptr; prev = curr, curr = curr->uBuff.uNextPtr) {

        if (curr->uBuff.uSize >= normalizedunits) {

            if (curr->uBuff.uSize == normalizedunits) {

                if (prev) {

                    prev->uBuff.uNextPtr = curr->uBuff.uNextPtr;
                    curr->uBuff.uPrevPtr = prev;
                } else {

                    gFree = gFree -> uBuff.uNextPtr;
                    gFree->uBuff.uPrevPtr = nullptr;
                }
            } else {

                curr->uBuff.uSize = curr->uBuff.uSize - normalizedunits;
                curr = curr + curr->uBuff.uSize;
                curr -> uBuff.uSize = normalizedunits;
            }
            (curr + curr->uBuff.uSize - 1) -> uBuff.uSize = curr->uBuff.uSize;			
            curr -> uBuff.uFlag = false;
            return (void *)(curr + 1);
        }
    }
    if ((gFree = GetMemoryFromOS(normalizedunits)) == NULL) {

        return NULL;
    }

    return Malloc(pSize);
}

#endif
