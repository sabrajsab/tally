#ifndef CUSTOMIO_HXX
#define CUSTOMIO_HXX

#include <stdio.h>
#include <stdlib.h>

int print (int val)
{
    return printf("%d", val);
}

int print (float val)
{
    return printf("%f", val);
}

int print (double val)
{
    return printf("%lf", val);
}

int print (char val)
{
    return printf("%c", val);
}

int print (char * val)
{
    return printf("%s", val);
}

int print (const char * val)
{
    return printf ("%s", val);
}
int print (string str)
{
    str.Display();
    return str.Size();
}

/** 
 * @brief takes input from console using getchar() and evaluates 
 *        input based on template data type
 *  
 * @param <T> no parameters
 * 
 * @return evaluated value for the data type
 */
template <class T>
T scan()
{
    ;
}

/**
 * @brief takes input from console using getchar() and evaluates 
 *        corresponding integer value
 *        Keeps on asking to enter integer value (max no of
 *        times) till user provides valid integer value
 * 
 * @return int calculated integer value
 */
template<>
int scan()
{
    return scanInt();
}

template<>
float scan()
{
    return scanFloat();
}

template<>
double scan()
{
    return scanDouble();
}

template<>
char scan()
{
        char ch = getchar ();
    if (ch == '\n') {

        return scan<char> ();
    }
    while (getchar() != '\n');

    return ch;
}

template<>
char * scan()
{
    return scanString ();
}

int scanInt (int repeat)
{
    if (repeat >= 5) {
        
        printf("Maximum Trials reached. Taking 0 as default input");
        return 0;
    }

        int          neg           = 1;
        int          val           = 0;
        bool         isNotInt      = false;
        register int c             = getchar ();
        int          digits        = 0;
        static   int maxNoOfDigits = 8;

	if (c == '\n') {
		
		printf ("\nTaking default value : 10\n");
		return 10;
	}
    if (c == '-') {

        neg = -1;
        c = getchar();
    }
    do {

        if (c < '0' || c > '9') {

            isNotInt = true;
            break;
        }
        digits++;
        val *= 10;
        val += (c - '0');
    } while ((c = getchar ()) != '\n' && c != ' ');

    if (isNotInt) {

        while ((getchar()) != '\n');
        printf("Please enter integer value\n");
        return scanInt (++repeat);
    }

    if (digits >= maxNoOfDigits) {
        if (c == ' ') {

            while ((getchar()) != '\n');
        }
        printf("No. of Digits exceeded maximum. Enter again\n");
        return scanInt (++repeat);
    }

    return val * neg;
}

bool CheckInt (char * pStr, int & pVal)
{
        int          neg           = 1;
        int          val           = 0;
        bool         isNotInt      = false;
		int 		 index		   = 0;
        register int c             = pStr [index ++];
        int          digits        = 0;
        static   int maxNoOfDigits = 8;

    if (c == '-') {

        neg = -1;
        c = pStr [index ++];
    } else if (c == '+') {
		
		c = pStr [index ++];
	}
    do {

        if (c < '0' || c > '9') {

            isNotInt = true;
            break;
        }
        digits++;
        val *= 10;
        val += (c - '0');
    } while ((c = pStr [index ++]) != '\n' && c != ' ' && c != '\0');

    if (isNotInt) {

        while ((pStr [index ++]) != '\n');
        printf("Please enter integer value\n");
        return false;
    }

    if (digits >= maxNoOfDigits) {
        if (c == ' ') {

            while ((pStr [index ++]) != '\n');
        }
        printf("No. of Digits exceeded maximum.\n");
        return false;
    }

    pVal = val * neg;
	return true;
}

char * scanString ()
{
        char   ch;
        int    size {0};
        char * str  {nullptr};
        int    maximum_string_len = 30;

    while (1) {

        if ((size + 10) >= maximum_string_len) {

            printf("\nEntered string too long. Taking first %d characters", size - 1);
            str[size - 1] = '\0';
            return str;
        }
        str = allocateMoreSpace(str, size);
        size += 10;
        for (int i = 10; i >= 0; --i) {

            if ((ch = getchar ()) == '\n') {

                str[size - i]='\0';
                return str;
            }
            str[size - i] = ch;
        }

    }
}

int scanPositiveInt (int repeat)
{

    if (repeat >= 5) {

        printf("Maximum Trials reached. Taking 0 as default input\n");
        return 0;
    }

        int          neg           = 1;
        int          val           = 0;
        bool         isNotInt      = false;
        register int c             = getchar ();
        int          digits        = 0;
        static   int maxNoOfDigits = 8;

    if (c == '-') {

        neg = -1;
        c = getchar();
    }
    do {

        if (c < '0' || c > '9') {

            isNotInt = true;
            break;
        }
        digits++;
        val *= 10;
        val += (c - '0');
    } while ((c = getchar ()) != '\n' && c != ' ');

    if (isNotInt) {

        while ((getchar()) != '\n');
        printf("Please enter integer value\n");
        return scanPositiveInt (++repeat);
    }

    if (digits >= maxNoOfDigits) {
        if (c == ' ') {

            while ((getchar()) != '\n');
        }
        printf("No. of Digits exceeded maximum. Enter again\n");
        return scanPositiveInt (++repeat);
    }

    if (neg == -1) {

        if (c == ' ') {

            while ((getchar()) != '\n');
        }
        printf("please enter positive value.\n");
        return scanPositiveInt(++repeat);
    }

    return val * neg;
}

float scanFloat (int repeat)
{
    if (repeat >= 5) {
        
        printf("Maximum Trials reached. Taking 0 as default input");
        return 0;
    }

        int          neg           = 1;
        float        val           = 0;
        float        decimalVal    = 0;
        bool         isNotFloat    = false;
        register int c             = getchar ();
        int          noOfDots      = 0;
        int          digits        = 0;
        int          decimalDigits = 0;
        static   int maxNoOfDigits = 37;
        static   int maxDecDigits  = 9;

    if (c == '-') {

        neg = -1;
        c = getchar();
    }
    do {

        if ((c < '0' || c > '9') && c != '.') {

            isNotFloat = true;
            break;
        }
        if (c == '.') {
            
            noOfDots = 1;
            break;
        }
        digits++;
        val *= 10;
        val += (c - '0');
    } while ((c = getchar ()) != '\n' && c != ' ');

    while (c != '\n' && c != ' ' && decimalDigits < 10) {

        if ((c < '0' || c > '9')  && c != '.') {

            isNotFloat = true;
            break;
        }
        c = getchar ();

        if (c == '.') {

            isNotFloat = true;
            break;
        }
        decimalVal *= 10;
        decimalVal += (c - '0');
        decimalDigits++;
    }

    if (isNotFloat) {

        while ((getchar()) != '\n');
        printf("Please enter float value\n");
        return scanFloat (++repeat);
    }

    if (digits >= maxNoOfDigits) {
        if (c == ' ') {

            while ((getchar()) != '\n');
        }
        printf("No. of Digits exceeded maximum. Enter again\n");
        return scanFloat (++repeat);
    }

    val += (decimalVal / pow(10, decimalDigits));
    return val * neg;
}


int pow (int a, int b)
{
    if (b == 0) {
        return 1;
    }
    return a * pow (a, b - 1);
}


double scanDouble (int repeat)
{
    if (repeat >= 5) {
        
        printf("Maximum Trials reached. Taking 0 as default input");
        return 0;
    }

        int          neg           = 1;
        double       val           = 0;
        double       decimalVal    = 0;
        bool         isNotDouble   = false;
        register int c             = getchar ();
        int          noOfDots      = 0;
        int          digits        = 0;
        int          decimalDigits = 0;
        static   int maxNoOfDigits = 307;
        static   int maxDecDigits  = 9;

    if (c == '-') {

        neg = -1;
        c = getchar();
    }
    do {

        if ((c < '0' || c > '9') && c != '.') {

            isNotDouble = true;
            break;
        }
        if (c == '.') {
            
            noOfDots = 1;
            break;
        }
        digits++;
        val *= 10;
        val += (c - 48);
    } while ((c = getchar ()) != 10 && c != 32);

    while (c != 10 && c != 32 && decimalDigits < 10) {

        if ((c < '0' || c > '9') && c != '.') {

            isNotDouble = true;
            break;
        }
        c = getchar ();

        if (c == '.') {

            isNotDouble = true;
            break;
        }
        decimalVal *= 10;
        decimalVal += (c - '0');
        decimalDigits++;
    }

    if (isNotDouble) {

        while ((getchar()) != '\n');
        printf("Please enter Double value\n");
        return scanDouble (++repeat);
    }

    if (digits >= maxNoOfDigits) {
        if (c == ' ') {

            while ((getchar()) != '\n');
        }
        printf("No. of Digits exceeded maximum. Enter again\n");
        return scanDouble (++repeat);
    }

    val += (decimalVal / pow(10, decimalDigits));
    return val * neg;
}

char * allocateMoreSpace (char * str, int size)
{
        int i{0};
        char * newStr = (char *)malloc(sizeof(char) * (size + 10));
    if (newStr == nullptr){
        
        printf("\n cannot allocate more memory");
        free (newStr);
        return str;
    }
    if (size == 0) {
        
        return newStr;
    }
    for (i = 0; str[i] != '\0'; ++i) {

        newStr[i] = str[i];
    }
    newStr[i] = '\0';
    free (str);
    return newStr;
}

#endif
