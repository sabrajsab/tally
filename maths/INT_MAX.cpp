int INT_MAX ()
{
    int noOfBits = 8 * sizeof (int);
    return pow (2, noOfBits - 1) - 1;
}
