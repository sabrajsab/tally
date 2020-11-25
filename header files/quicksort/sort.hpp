#ifndef SORT_HPP
#define SORT_HPP

/**
 * @brief swap 2 numbers of type long long
 * @param pParam1 1st number
 * @param pParam2 2nd number
 */
void Swap      (long long int *, long long int *);

/**
 * @brief fix the final position of the last element of the 
 *        array (i.e. pivot), with all elements lesser in the
 *        left and all elents higher than the pivot on the right
 * @param arr input array of long long numbers
 * @param pLow starting index
 * @param pHigh last index
 * 
 * @return int final index of the pivot
 */
int  Partition (long long int *, int, int);

/**
 * @brief recursively find and fix the final location of the 
 *        last element (i.e. pivot), with all elements lesser in
 *        the left and all elents higher than the pivot on the
 *        right
 * @param arr input array to sort
 * @param pLow starting index
 * @param pHigh last index
 */
void QuickSort (long long int *, int, int);

#include "sort.hxx"
#endif
