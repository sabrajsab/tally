#include <stdio.h>
#include <Windows.h>
#include "sort.hpp"
#include "mergesortedfiles.hpp"

#define batchsize 10
#define buffersize 12

int main ()
{
    HANDLE src;
    HANDLE dest;

    char source[] = "src/source.txt";
    char destination[] = "dest/dest.txt";

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

        char buff[buffersize] = {'\0'};
        char path [200];
        sprintf (path, "dest/%d.txt", filenum);
        HANDLE intermediate = CreateFileA (path, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        for (int j = 0; j < i; j++) {

            sprintf (buff, "%lld\r\n", arr[j]);
            WriteFile (intermediate, buff, buffersize, &bytes_written, NULL);
        }
        CloseHandle (intermediate);
        filenum++;
    }

    HANDLE * handle_arr = (HANDLE *) malloc ((filenum - 1) * sizeof(HANDLE));
    for (int i = 0; i < filenum - 1; ++i) {

        char path[20];
        sprintf (path, "dest/%d.txt", i + 1);
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

