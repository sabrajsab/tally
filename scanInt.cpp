//format of input : int a = scanInt (0);

int pow (int a, int b)
{
    if (b == 0) {
        return 1;
    }
    return a * pow (a, b - 1);
}

int IntMax ()
{
        int        noOfBits = 8 * sizeof (int);
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
        int          digits    = 0;
        static   int maxNoOfDigits = 0;

    if (maxNoOfDigits == 0) {

        maxNoOfDigits = noOfDigits (IntMax ());
    }
    if (c == '-') {

        neg = -1;
        c = getchar();
    }
    do {

        if (c<48 || c>57) {

            isNotInt = true;
        }
        digits++;
        val *= 10;
        val += (c - 48);
    } while ((c = getchar ()) != 10 && c != 32);

    if (isNotInt) {

        if (c == 32) {

            while ((getchar()) != '\n');
        }
        printf("Please enter integer value\n");
        return scanInt (++repeat);
    }

    if (digits >= maxNoOfDigits) {
        if (c == 32) {

            while ((getchar()) != '\n');
        }
        printf("No. of Digits exceeded maximum. Enter again\n");
        return scanInt (++repeat);
    }

    return val * neg;
}
