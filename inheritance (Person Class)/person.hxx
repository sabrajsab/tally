#ifndef PERSON_HXX
#define PERSON_HXX

char * Person :: GetName ()
{
    return rName;
}

int Person :: GetAge ()
{
    return rAge;
}

int Person :: GetSalary ()
{
    return rSalary;
}

void Person :: TakeInput () {}

void Person :: Display   () {}

     Person :: ~Person   () {}

bool CompareName (Person * pPtr1, Person * pPtr2)
{
        string s1 (pPtr1 -> GetName());
        string s2 (pPtr2 -> GetName());
    return (s1 > s2);
}

bool CompareAge (Person * pPtr1, Person * pPtr2)
{
    return (pPtr1 -> GetAge ()) > (pPtr2 -> GetAge ());
}

bool CompareSalary (Person * pPtr1, Person * pPtr2)
{
    return (pPtr1 -> GetSalary ()) > (pPtr2 -> GetSalary ());
}

#endif
