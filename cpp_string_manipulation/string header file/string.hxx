#ifndef STRING_HXX
#define STRING_HXX

#include <iostream>


int sizeOf (const char * pStr) {

        int i;
    for     (i = 0; pStr [i] != '\0'; ++i);
    return  (i + 1);
}

string :: string ()
{
    vLen     = 0;
    vSize    = 1;
    vArr     = (char *) malloc (1);
    vArr [0] = '\0';
}

string :: string (const char * pStr)
{
    vSize = sizeOf (pStr);
    vLen  = vSize - 1;
    vArr  = (char *) malloc (vSize);
    for (int i = 0; i <= vLen; ++i) {

        vArr [i] = pStr [i];
    }
}

string :: string (const string & pStr)
{
    vLen  = pStr.vLen;
    vSize = vLen + 1;
    vArr  = (char *) malloc (vSize);
    for (int i = 0; i <= vLen; ++i) {

        vArr [i] = pStr.vArr [i];
    }
}

int string :: Size ()
{
    return vLen;
}

string string :: operator = (string pStr)
{
    if (vSize >= pStr.vLen) {

        vLen = pStr.vLen;
        for (int i = 0; i <= vLen; ++i) {

            vArr [i] = pStr.vArr [i];
        }
        return * this;
    }

    vLen              = pStr.vLen;
    vSize             = vLen + 1;
        char * newPtr = (char *) realloc (vArr, vSize);

    if (!newPtr) {

        string newStr;
        return newStr;
    }

    vArr = newPtr;
    for (int i = 0; i <= vLen; ++i) {

        vArr [i] = pStr.vArr [i];
    }
    return * this;
}

string string :: operator = (const char * pStr)
{
    if (vSize >= sizeOf (pStr)) {

        vLen = (sizeOf (pStr)) - 1;
        for (int i = 0; i <= vLen; ++i) {

            vArr [i] = pStr [i];
        }
        return * this;
    }

        vSize     = sizeOf (pStr);
        vLen      = vSize - 1;
    char * newPtr = (char *) realloc (vArr, vSize);

    if (!newPtr) {

        string newStr;
        return newStr;
    }

    vArr = newPtr;

    for (int i = 0; i <= vLen; ++i) {

        vArr [i] = pStr [i];
    }
    return * this;
}

bool string :: operator == (string pStr)
{
    if (pStr.vLen == vLen) {

        for (int i = 0; i <= vLen; ++i) {

            if (vArr [i] != pStr.vArr [i]) {

                return false;
            }
        }

        return true;
    }

    return false;
}

void string :: Display ()
{
    printf("\n%s", vArr);
}

string :: ~string ()
{
    free (vArr);
}

#endif
