#include <stdio.h>
#include <Windows.h>
#include "sort.hpp"
#include "mergesortedfiles.hpp"

#define batchsize 5
#define buffersize 12

int main ()
{
    HANDLE src;
    HANDLE dest;

    char source[] = "source.txt";
    char destination[] = "dest.txt";

    src = CreateFileA (source, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    dest = CreateFileA (destination, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    char buffer[buffersize];
    int readwritesize = buffersize;
    int size = GetFileSize (src, NULL);
    DWORD bytes_read;
    long long arr[batchsize];
    int filenum = 1;

    while (size > 0) {

        DWORD bytes_written;
        int i;
        for (i = 0; i < batchsize && size > 0; i++) {

            if (size < readwritesize) {

                readwritesize = size;
            }
            ReadFile(src, buffer, readwritesize, &bytes_read, NULL);
            size = size - readwritesize;
            sscanf (buffer, "%lld", &arr[i]);
        }
        QuickSort (arr, 0, i - 1);
        char buff[buffersize * batchsize] = {'\0'};
        int k = 0;
        for (int j = 0; j < i; j++) {
            int num[10], n = 0;
            while (arr[j] > 0) {

               num[n] = arr[j] % 10;
               arr[j] = arr[j] / 10;
               n++;
            }
            n--;
            while (n >= 0) {

                buff[k] = num[n] + '0';
                n--;
                k++;
            }
            buff[k] = '\r';
            buff[k+1] = '\n';
            k = k + 2;
        }
        char path[200];
        sprintf (path, "%d.txt", filenum);
        filenum++;
        HANDLE intermediate = CreateFileA (path, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        WriteFile (intermediate, buff, (i * buffersize), &bytes_written, NULL);
        CloseHandle (intermediate);
    }

    HANDLE * handle_arr = (HANDLE *) malloc ((filenum - 1) * sizeof(HANDLE));
    for (int i = 0; i < filenum - 1; ++i) {

        char path[20];
        sprintf (path, "%d.txt", i + 1);
        handle_arr [i] = CreateFileA (path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    }

    MergeSortedFiles (handle_arr, filenum - 1, dest);

    for (int i = 0; i < filenum - 1; i++) {

        CloseHandle (handle_arr[i]);
    }
    free (handle_arr);
    CloseHandle (src);
    CloseHandle (dest);
    return 0;
}

