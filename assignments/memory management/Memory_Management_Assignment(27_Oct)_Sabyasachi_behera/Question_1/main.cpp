#include <stdio.h>
#include "genpurposeallocator.hpp"

int main ()
{
    int * p1 = (int *) Malloc (409);
    int * p2 = (int *) Malloc (239);
    int * p3 = (int *) Malloc (239);
    int * p4 = (int *) Malloc (239);
    Free (p1);
    Free (p3);
    Free (p2);
    int * p5 = (int *) Malloc (985);
    printf("%p\n", p1);
    printf("%p\n", p2);
    printf("%p\n", p3);
    printf("%p\n", p4);
    printf("%p\n", p5);
    return 0;
}

