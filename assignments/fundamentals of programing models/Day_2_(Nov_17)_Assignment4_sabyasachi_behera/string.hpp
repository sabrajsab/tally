#ifndef STRING_HPP
#define STRING_HPP
#include <stdlib.h>

class string {

	/*  vLen is no. of characters before '\0' in vArr
		vSize is total no. of bytes allocated for vArr
		vArr has always a '\0'
	*/
    private:
        int             vLen;
        int             vSize;
        char          * vArr;

    public:
                                 string  ();
                                 string  (const char *);
                                 string  (string &);
               int               Size    ();

               string & operator =       (string &);
               string & operator =       (const char *);

               bool     operator ==      (string &);
               bool     operator ==      (const char *);
        friend bool     operator ==      (const char *, string &);

               bool     operator !=      (string &);
               bool     operator !=      (const char *);
        friend bool     operator !=      (const char *, string &);

        friend bool     operator >       (string &, const char *);
        friend bool     operator >       (const char *, string &);
               bool     operator >       (string &);

        friend bool     operator <       (string &, const char *);
        friend bool     operator <       (const char *, string &);
               bool     operator <       (string &);

        friend bool     operator >=      (string &, const char *);
        friend bool     operator >=      (const char *, string &);
               bool     operator >=      (string &);

        friend bool     operator <=      (string &, const char *);
        friend bool     operator <=      (const char *, string &);
               bool     operator <=      (string &);

        friend string   operator +       (const char *, string &);
               string   operator +       (const char *);
        friend string   operator +       (string &, string &);

               string & operator +=      (const char *);

				        operator char *  ();
               char   & operator []      (int);

               void              Display ();
               int 		         ToInt ();
               int 		         Compare (const char *);

                                 ~string  ();
};

int sizeOf (const char * str);

#include "string.hxx"
#endif

