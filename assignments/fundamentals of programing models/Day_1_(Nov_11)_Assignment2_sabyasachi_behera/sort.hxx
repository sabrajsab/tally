#ifndef SORT_HXX
#define SORT_HXX


void Swap (long long int * a, long long int * b)
{
    long long int t = *a;
    *a = *b;
    *b = t;
}

int Partition (long long int arr[], int low, int high)
{
    long long int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {

        if (arr[j] < pivot) {

            i++;
            Swap (&arr[i], &arr[j]);
        }
    }
    Swap (&arr[i + 1], &arr[high]);
    return (i + 1);
}

void QuickSort (long long int arr[], int low, int high)
{
    if (low < high) {

        int pi = Partition (arr, low, high);

        QuickSort (arr, low, pi - 1);
        QuickSort (arr, pi + 1, high);
    }
}

#endif
