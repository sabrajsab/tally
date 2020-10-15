#ifndef TEACHER_HXX
#define TEACHER_HXX

#include <iostream>
#include "customio.hpp"

void Teacher :: TakeInput ()
{
    printf("\nEnter Name, age, salary, subject\n");
    rName    = scan <char *> ();
    rAge     = scan <int>    ();
    rSalary  = scan <int>    ();
    vSubject = scan <char *> ();
}
void Teacher :: Display ()
{
    printf ("\nName : %s, Age : %d, Salary : %d, Subject Name : %s\n", rName, rAge, rSalary, vSubject);
}

     Teacher :: ~Teacher ()
{

}
#endif
