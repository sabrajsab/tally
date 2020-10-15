#ifndef PERSON_HPP
#define PERSON_HPP
#include "string.hpp"

class Person {

    protected :

        char       * rName;
        int          rAge;
        int          rSalary;
    public :

        char       * GetName   ();
        
        int          GetAge    ();

        int          GetSalary ();
        
        virtual void TakeInput ();

        virtual void Display   ();

        virtual     ~Person    ();         
};

bool CompareName (Person * pPtr1, Person * pPtr2);

bool CompareAge (Person * pPtr1, Person * pPtr2);

bool CompareSalary (Person * pPtr1, Person * pPtr2);


#include "person.hxx"
#endif
