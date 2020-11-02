#include <stdio.h>
#include <stdlib.h>
#include "ref_ptr.hpp"

struct s{
    int n=10;
};

int main ()
{
    RefPtr <char> p1 (new char ('a'), false);
    char * ch = p1;
    printf ("typecasting to char *, *ch = %c, *p1 = %c\n", *ch, *p1);

    RefPtr <int> p2 (new int (10), false);
    int * n = p2;
    printf ("typecasting to int *, *n = %d, *p2 = %d\n", *n, *p2);

    RefPtr <int> p3 (p2);
    printf ("p3 initialize by copy constructor, *p3 = %d\n", *p3);

    RefPtr <int> p4 (new int (20), false);
    p4 = p2;
    printf ("assignment operator for p4, *p4 = %d\n", *p4);

    printf ("overloading == operator, p2 == p3 %d, p2 == p4 %d\n", p2 == p3, p2 == p4);

    RefPtr <s> p5 (new s, false);
    printf ("p5->n = %d\n", p5->n);

    try {
        
        RefPtr<int> * p6 = new RefPtr<int>(n);
    }
    catch (std::bad_alloc) {

        printf ("Can not allocate memory on heap...\n");
    }

    RefPtr <int> p7, p8;
    p8 = p7 = p2;
    printf ("*p7 = %d, *p8 = %d", *p7, *p8);

    return 0;
}

