//takes input positive integer nothing else

int scanPositiveInt ()
{
    int neg=1,val=0;
    bool isNotInt=false;
    register int c=getchar();
    if(c=='-')
    {
        neg=-1;
        c=getchar();
    }
    do
    {
        if (c<48 || c>57) {
            isNotInt=true;
        }
        val*=10;
        val+=(c-48);
    }while((c=getchar())!=10 && c !=32);

    if (isNotInt) {
        if (c == 32) {
            while ((getchar()) != '\n');
        }
        printf("Please enter integer value\n");
        return scanPositiveInt();
    }

    if (neg==-1) {
        if (c == 32) {
            while ((getchar()) != '\n');
        }
        printf("please enter positive value.\n");
        return scanPositiveInt();
    }

    return val*neg;
}
