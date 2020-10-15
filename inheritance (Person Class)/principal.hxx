#ifndef PRINCIPAL_HXX
#define PRINCIPAL_HXX

#include <iostream>
#include "customio.hpp"

void Principal :: TakeInput ()
{
    print ("\nEnter Name, age, salary, Name of School\n");
    rName       = scan <char *> ();
    rAge        = scan <int>    ();
    rSalary     = scan <int>    ();
    vSchoolName = scan <char *> ();
}
void Principal :: Display ()
{
    printf ("\nName : %s, Age : %d, Salary : %d, School Name : %s\n", rName, rAge, rSalary, vSchoolName);
}

     Principal :: ~Principal ()
{

}

#endif
