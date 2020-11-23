#ifndef CUSTOMIO_HPP
#define CUSTOMIO_HPP
#include "string.hpp"

int print (int val);

int print (float val);

int print (double val);

int print (char val);

int print (char * val);

int print (const char *);

int print (string);

template <class T>
T scan();

int scanPositiveInt(int size = 0);

int scanInt(int size = 0);

float scanFloat(int size = 0);

double scanDouble(int size = 0);

char * scanString ();

int pow (int, int);

char * allocateMoreSpace (char * str, int size);

#include "customio.hxx"

#endif
