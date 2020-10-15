#ifndef PRINCIPAL_HPP
#define PRINCIPAL_HPP

#include "person.hpp"

class Principal : public Person {
    private :

        char * vSchoolName;

    public :

        void   TakeInput ();

        void   Display   ();

              ~Principal ();
};

#include "principal.hxx"
#endif
