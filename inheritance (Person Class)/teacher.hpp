#ifndef TEACHER_HPP
#define TEACHER_HPP

#include "person.hpp"

class Teacher : public Person
{
    private :

        char * vSubject;

    public :

        void   TakeInput ();

        void   Display   ();

              ~Teacher   ();
};

#include "teacher.hxx"
#endif
