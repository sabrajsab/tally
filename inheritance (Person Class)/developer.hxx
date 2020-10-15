#ifndef DEVELOPER_HXX
#define DEVELOPER_HXX

#include <iostream>
#include "customio.hpp"

void Developer :: TakeInput ()
{
    printf("\nEnter Name, age, salary, his fav programming language\n");
    rName                  = scan <char *> ();
    rAge                   = scan <int>    ();
    rSalary                = scan <int>    ();
    vFavProgramminLanguage = scan <char *> ();
}
void Developer :: Display ()
{
     printf ("\nName : %s, Age : %d, Salary : %d, fav programming language : %s\n",
             rName, rAge, rSalary, vFavProgramminLanguage);
}

     Developer :: ~Developer ()
{

}

#endif
