#ifndef GENPURPOSEALLOCATOR_CPP
#define GENPURPOSEALLOCATOR_CPP

#include <stdio.h>
#include <Windows.h>
#include <stdint.h>
#include "genpurposeallocator.hpp"

const int       gcMaxSz = 50;
static Header   gBase;
static Header * gFree;

void Init ()
{
    if (gFree == NULL) {

        gBase.uBuff.uPtr = gFree = &gBase;
        gBase.uBuff.uSize = 0;
    }
}

void Free (void * pPtrToFree)
{
    Header * headerofmemtofree;
    Header * scan;

    headerofmemtofree = (Header *) pPtrToFree - 1;

    for (scan = gFree; scan->uBuff.uPtr != gFree; scan = scan->uBuff.uPtr) {

        if (scan < headerofmemtofree && scan->uBuff.uPtr > headerofmemtofree) {

            break;
        }
    }

    if ((headerofmemtofree + headerofmemtofree->uBuff.uSize) == scan->uBuff.uPtr) {

        headerofmemtofree->uBuff.uSize += scan->uBuff.uPtr->uBuff.uSize;
        headerofmemtofree->uBuff.uPtr = scan->uBuff.uPtr->uBuff.uPtr;
    } else {

        headerofmemtofree->uBuff.uPtr = scan->uBuff.uPtr;
    }

    if ((scan + scan->uBuff.uSize) == headerofmemtofree) {

        scan->uBuff.uSize += headerofmemtofree->uBuff.uSize;
        scan->uBuff.uPtr = headerofmemtofree->uBuff.uPtr;
    } else {

        scan->uBuff.uPtr = headerofmemtofree;
    }

    gFree = scan;
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

    Free ((void *)(up + 1));

    return gFree;
}

void * Malloc (unsigned pSize)
{
    Header * prev;
    uint32_t normalizedunits;

    normalizedunits = (pSize + sizeof (Header) - 1) / sizeof (Header) + 1;
    Init ();
    prev = gFree;

    for (Header * curr = prev->uBuff.uPtr; ; prev = curr, curr = curr->uBuff.uPtr) {

        if (curr->uBuff.uSize >= normalizedunits) {

            if (curr->uBuff.uSize == normalizedunits) {

                prev->uBuff.uPtr = curr->uBuff.uPtr;
            } else {

                curr->uBuff.uSize = curr->uBuff.uSize - normalizedunits;
                curr = curr + curr->uBuff.uSize;
                curr->uBuff.uSize = normalizedunits;
            }
            gFree = prev;
            return (void *)(curr + 1);
        }

        if (curr == gFree) {

            if ((gFree = GetMemoryFromOS(normalizedunits)) == NULL) {

                return NULL;
            }
        }
    }
}

void * Calloc (unsigned pNumberOfElements, unsigned pSize)
{
    unsigned size = pNumberOfElements * pSize;
    void * ptr = Malloc (size);
    if (ptr != NULL) {

        memset (ptr, 0, size);
    }
    return ptr;
}

#endif
