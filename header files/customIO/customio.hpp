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

/** 
 * @brief takes input from console using getchar() and evaluates 
 *        input based on template data type
 *  
 * @param <T> no parameters
 * 
 * @return T evaluated value for the data type
 */
template <class T>
T scan();

int scanPositiveInt(int size = 0);

/**
 * @brief takes input from console using getchar() and evaluates 
 *        corresponding integer value
 *        Keeps on asking to enter integer value (max no of
 *        times) till user provides valid integer value
 * 
 * @return int calculated integer value
 */
int scanInt(int size = 0);

float scanFloat(int size = 0);

double scanDouble(int size = 0);

char * scanString ();

int pow (int, int);

char * allocateMoreSpace (char * str, int size);

#include "customio.hxx"

#endif
