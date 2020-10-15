#ifndef MATHS_HXX
#define MATHS_HPP

int pow (int a, int b) {
	
	if(b == 1) {
		
		return 1;
	}
	return a * pow (a, b-1);
}

int INT_MAX ()
{
    int noOfBits = 8 * sizeof (int);
    return pow (2, noOfBits - 1) - 1;
}

#endif