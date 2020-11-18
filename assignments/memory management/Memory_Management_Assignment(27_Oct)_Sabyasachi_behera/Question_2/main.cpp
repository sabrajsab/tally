
#include <stdio.h>
#include "genpurposeallocator.hpp"

int main ()
{
    int * p1 = (int *) Malloc (385);
    int * p2 = (int *) Calloc (5, 29);
    int * p3 = (int *) Malloc (145);
    Free (p2);
    int * p4 = (int *) Malloc (145);
    return 0;
}

