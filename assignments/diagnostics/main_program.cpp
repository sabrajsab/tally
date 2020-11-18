#include <windows.h>
#include <stdio.h>
#include <strsafe.h>
#include<assert.h>
#include "Logger.hpp"
#define BUFFERSIZE 100
Logger logger;
int add(int a, int b) {
	logger.log( "add () execution starting");
	if (a > 100) {
	
		logger.log("a is more that 100", ERRORS);
	}
		int sum = a + b;
	logger.log("add() execution ending");
	return sum;
}
int main(int argc, char ** argv)
{
	int a, b;
	a = 10;
	b = 20;
	logger.log("a = 10, b = 20", INFO);
	logger.log("calling add function");
	int d = add(a,b);
	assert(d == 30);

    system("pause");
    return 0;
}

