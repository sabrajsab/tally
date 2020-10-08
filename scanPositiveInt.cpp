//format of scan : int a = scanPositiveInt (0);



int pow (int a, int b)
{
    if (b == 0) {
        return 1;
    }
    return a * pow (a, b - 1);
}

int IntMax ()
{
        int        noOfBits  = 8 * sizeof (int);
        static int returnVal = 0;
    
    if (returnVal == 0) {
        returnVal = (pow(2, noOfBits - 1) - 1);
    }
    return returnVal;
}

int noOfDigits (int num)
{
        int nod = 0;
    while (num) {

        nod++;
        num /= 10;
    }
    return nod;
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
        static   int maxNoOfDigits = 0;

    if (maxNoOfDigits == 0) {

        maxNoOfDigits = noOfDigits (IntMax ());
    }
    if (c == '-') {

        neg = -1;
        c = getchar();
    }
    do {

        if (c < '0' || c > '\n') {

            isNotInt = true;
        }
        digits++;
        val *= 10;
        val += (c - '0');
    } while ((c = getchar ()) != '\n' && c != ' ');

    if (isNotInt) {

        if (c == ' ') {

            while ((getchar()) != '\n');
        }
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

