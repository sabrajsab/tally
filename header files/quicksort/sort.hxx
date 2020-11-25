#ifndef SORT_HXX
#define SORT_HXX

/**
 * @brief swap 2 numbers of type long long
 * @param pParam1 1st number
 * @param pParam2 2nd number
 */
void Swap (long long int * pParam1, long long int * pParam2)
{
    long long int temp = *pParam1;
    *pParam1 = *pParam2;
    *pParam2 = temp;
}

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
int Partition (long long int arr [], int pLow, int pHigh)
{
    long long int pivot = arr [pHigh];
    int i = (pLow - 1);
    for (int j = pLow; j <= pHigh - 1; j++) {

        if (arr[j] < pivot) {

            i++;
            Swap (&arr [i], &arr [j]);
        }
    }
    Swap (&arr [i + 1], &arr [pHigh]);
    return (i + 1);
}

/**
 * @brief recursively find and fix the final location of the 
 *        last element (i.e. pivot), with all elements lesser in
 *        the left and all elents higher than the pivot on the
 *        right
 * @param arr input array to sort
 * @param pLow starting index
 * @param pHigh last index
 */
void QuickSort (long long int arr [], int pLow, int pHigh)
{
    if (pLow < pHigh) {

        int pi = Partition (arr, pLow, pHigh);

        QuickSort (arr, pLow, pi - 1);
        QuickSort (arr, pi + 1, pHigh);
    }
}

#endif
