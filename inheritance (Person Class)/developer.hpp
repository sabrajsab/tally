#ifndef DEVELOPER_HPP
#define DEVELOPER_HPP

#include "person.hpp"

class Developer : public Person
{
    private :

        char * vFavProgramminLanguage;

    public :

        void   TakeInput ();

        void   Display   ();

              ~Developer ();
};

#include "developer.hxx"
#endif
