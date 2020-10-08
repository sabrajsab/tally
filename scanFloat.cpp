
int pow (int a, int b)
{
    if (b == 0) {
        return 1;
    }
    return a * pow (a, b - 1);
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
        bool         isNotInt      = false;
        register int c             = getchar ();
        int          noOfDots      = 0;
        int          digits        = 0;
        int          decimalDigits = 0;
        static   int maxNoOfDigits = 37;

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
        val += (c - 48);
    } while ((c = getchar ()) != 10 && c != 32);

    while (c != 10 && c != 32 && decimalDigits < 10) {

        c = getchar ();
        if (c<48 || c>57) {

            isNotFloat = true;
            break;
        }
        decimalVal *= 10;
        decimalVal += (c - '0');
        decimalDigits++;
    }

    if (isNotFloat) {

        if (c == 32) {

            while ((getchar()) != '\n');
        }
        printf("Please enter float value\n");
        return scanFloat (++repeat);
    }

    if (digits >= maxNoOfDigits) {
        if (c == 32) {

            while ((getchar()) != '\n');
        }
        printf("No. of Digits exceeded maximum. Enter again\n");
        return scanFloat (++repeat);
    }

    val += (decimalVal / pow(10, decimalDigits));
    return val * neg;
}
