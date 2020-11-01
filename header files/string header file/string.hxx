#ifndef STRING_HXX
#define STRING_HXX

#include <iostream>

/*  return no. of characters including '\0'
	e.g. for "hello" it returns 6
*/
int sizeOf (const char * pStr) {

        int i;
    for     (i = 0; pStr [i] != '\0'; ++i);
    return  (i + 1);
}

string :: string ()
{
    vLen     = 0;
    vSize    = 10;
    vArr     = (char *) malloc (sizeof(char) * 10);
    vArr [0] = '\0';
}

string :: string (const char * pStr)
{
    vSize = sizeOf (pStr);
    vLen  = vSize - 1;
    vSize = ((vSize / 10) + 1) * 10;
    vArr  = (char *) malloc (vSize);
    for (int i = 0; i <= vLen; ++i) {

        vArr [i] = pStr [i];
    }
}

string :: string (string & pStr)
{
    vLen  = pStr.Size();
    vSize = vLen + 1;
    vSize = ((vSize / 10) + 1) * 10;
    vArr  = (char *) malloc (vSize);
    for (int i = 0; i <= vLen; ++i) {

        vArr [i] = pStr.vArr [i];
    }
}

int string :: Size ()
{
    return vLen;
}

string & string :: operator = (string & pStr)
{
    return (*this) = (char *) pStr;
}

string & string :: operator = (const char * pStr)
{
    int pStr_size = sizeOf (pStr);
    if (vSize >= pStr_size) {

        vLen = (pStr_size) - 1;
        for (int i = 0; i <= vLen; ++i) {

            vArr [i] = pStr [i];
        }
        return * this;
    }

        vSize     = ((pStr_size / 10) + 1) * 10;
    char * newPtr = (char *) malloc (sizeof (char) * vSize);

    if (!newPtr) {

        return * this;
    }
    for (int i = 0; i <= vLen; ++i) {

            newPtr [i] = vArr [i];
        }
    free (vArr);
    vArr = newPtr;

    vLen = pStr_size - 1;
    for (int i = 0; i <= vLen; ++i) {

        vArr [i] = pStr [i];
    }

    return * this;
}

bool string :: operator == (string & pStr)
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

bool string :: operator == (const char * pStr)
{
    if (vLen == (sizeOf(pStr) -1)) {

        for (int i = 0; i <= vLen; ++i) {

            if (vArr [i] != pStr [i]) {

                return false;
            }
        }

        return true;
    }

    return false;
}

bool operator == (const char * pStr, string & pThis)
{
    return (pThis == pStr);
}

bool string :: operator != (string & pStr)
{
    if (pStr.vLen == vLen) {

        for (int i = 0; i <= vLen; ++i) {

            if (vArr [i] != pStr.vArr [i]) {

                return !false;
            }
        }

        return !true;
    }

    return !false;
}

bool string :: operator != (const char * pStr)
{
    if (vLen == (sizeOf(pStr) -1)) {

        for (int i = 0; i <= vLen; ++i) {

            if (vArr [i] != pStr [i]) {

                return !false;
            }
        }

        return !true;
    }

    return !false;
}

bool operator != (const char * pStr, string & pThis)
{
    return !(pThis == pStr);
}

bool operator > (string & pThis, const char * pStr)
{
        int pStr_size = sizeOf(pStr) - 1;
    for (int i = 0; i < pThis.Size() && i < pStr_size; ++i) {

        if (pThis [i] < pStr [i]) {

            return false;
        } else if (pThis [i] > pStr [i]) {

            return true;
        }
    }
    if (pThis.Size() > pStr_size) {

        return true;
    }

    return false;
}

bool operator > (const char * pStr, string & pThis)
{
        int pStr_size = sizeOf(pStr) - 1;
    for (int i = 0; i < pThis.Size() && i < pStr_size; ++i) {

        if (pThis [i] > pStr [i]) {

            return false;
        } else if (pThis [i] < pStr [i]) {

            return true;
        }
    }
    if (pThis.Size() < pStr_size) {

        return true;
    }

    return false;
}

bool string :: operator > (string & pStr)
{
        int pStr_size = pStr.Size();
    for (int i = 0; i < Size() && i < pStr_size; ++i) {

        if (vArr [i] < pStr [i]) {

            return false;
        } else if (vArr [i] > pStr [i]) {

            return true;
        }
    }
    if (Size() > pStr_size) {

        return true;
    }

    return false;
}

bool operator < (string & pThis, const char * pStr)
{
    return pStr > pThis;
}

bool operator < (const char * pStr, string & pThis)
{
    return (pThis > pStr);
}

bool string :: operator < (string & pStr)
{
    return (pStr > (*this));
}

bool operator >= (string & pThis, const char * pStr)
{
    return (pStr < pThis);
}

bool operator >= (const char * pStr, string & pThis)
{
    return (pThis < pStr);
}

bool string :: operator >= (string & pStr)
{
    return (pStr < *this);
}

bool operator <= (string & pThis, const char * pStr)
{
    return (pStr > pThis);
}

bool operator <= (const char * pStr, string & pThis)
{
    return (pThis > pStr);
}

bool string :: operator <= (string & pStr)
{
    return (pStr > *this);
}

string string :: operator + (const char * pStr)
{
	int pStr_size = sizeOf (pStr);
	if (vLen + pStr_size > vSize) {
		
		vSize = vLen + pStr_size;
        vSize = ((vSize / 10) + 1) * 10;
		char * newPtr = (char *) malloc (sizeof (char) * vSize);

		if (!newPtr) {

			string newStr;
			return newStr;
		}
        for (int i = 0; i <= vLen; ++i) {

            newPtr [i] = vArr [i];
        }
        free (vArr);
        vArr = newPtr;
	}
	for (int i = 0; i < pStr_size; ++i) {
		
		vArr [vLen + i] = pStr [i];
	}
	vLen += (pStr_size - 1);
	string temp (*this);
	vLen -= (pStr_size - 1);
	vArr [vLen] = '\0';
	return temp;
}

string operator + (const char * pStr, string & pThis)
{
        string temp_str (pStr);
        temp_str = temp_str + pThis;
        return temp_str;
}

string operator + (string & pThis, string & pStr)
{
        const char * temp = (char *) pStr;
	return (pThis + temp);
}

string :: operator char * ()
{
	return vArr;
}

char & string :: operator [] (int pIndex)
{
	return *(vArr + pIndex);
}

string & string :: operator += (const char * pStr)
{
    int pStr_size = sizeOf (pStr);
    if (vLen + pStr_size > vSize) {

        vSize = vLen + pStr_size;
        vSize = ((vSize / 10) + 1) * 10;
        char * newPtr = (char *) malloc (sizeof (char) * vSize);

        if (!newPtr) {

            return (* this);
        }
        for (int i = 0; i <= vLen; ++i) {

            newPtr [i] = vArr [i];
        }
        free (vArr);
        vArr = newPtr;
    }
    for (int i = 0; i < pStr_size; ++i) {

        vArr [vLen + i] = pStr [i];
    }
    vLen += (pStr_size - 1);
    return (* this);
}

void string :: Display ()
{
    printf("%s\n", vArr);
}

string :: ~string ()
{
    free (vArr);
}

int string :: ToInt ()
{
    int number = 0;
    for(int i = 0; vArr[i]!='\0'; ++i)
    {
        number *= 10;
        number += vArr[i] - '0';
    }
    return number;
}

int string :: Compare (const char * pStr)
{
	if ((* this) > pStr) {
		
		return 1;
	} else if ((* this) == pStr) {
		
		return 0;
	} else return -1;
}

#endif

