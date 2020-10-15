#ifndef STRING_HPP
#define STRING_HPP


class string {

    private:
        int             vLen;
        int             vSize;
        char          * vArr;

    public:
                        string  ();
                        string  (const char *);
                        string  (const string &);
        int             Size    ();
        string operator =       (const string &);
        string operator =       (const char *);
        bool   operator ==      (const string &);
        bool   operator >       (const string &);
        bool   operator ==      (const char *);
        void            Display ();
                       ~string  ();
};

int sizeOf (const char * str);

#include "string.hxx"
#endif
