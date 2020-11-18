#include <stdio.h>
#include "genpurposeallocator.hpp"

int main ()
{
    int * p1 = new int[100];
    int * p2 = new int[40];
    int * p3 = new int[40];
    delete p2;
    int * p4 = new int[40];
    return 0;
}

