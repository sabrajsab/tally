#include <stdio.h>
#include "auto_ptr.hpp"

int main ()
{
    AutoPtr<int> p1 = new int(5);

    AutoPtr<int> p2(p1);

    AutoPtr<int> p3, p4;
    p4 = p3 = p2;
    printf("%d", *p4);
    return 0;
}

