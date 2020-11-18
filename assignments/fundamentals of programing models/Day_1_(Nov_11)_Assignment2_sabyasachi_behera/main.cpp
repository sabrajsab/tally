#include <stdio.h>
#include <Windows.h>
#include "sort.hpp"
#include "mergesortedfiles.hpp"

#define BATCHSIZE  10
#define BUFFERSIZE 12

LARGE_INTEGER intToLargeInt(int i) {
    LARGE_INTEGER li;
    li.QuadPart = i;
    return li;
}

DWORD WINAPI mythread (__in LPVOID lpParameter)
{
        int       start_i           = * ((int *) lpParameter);
        int       start_index       = start_i * BATCHSIZE * BUFFERSIZE;
        long long arr[BATCHSIZE];
        int       i;
        HANDLE    src;
        char      buffer              [BUFFERSIZE];
        char      intermediate_name   [10];
        HANDLE    intermediate;
        DWORD     bytes_read;
        DWORD     bytes_written;

    sprintf            (intermediate_name, "%d.txt", (start_i + 1));

    src              = CreateFileA ("source.txt",      GENERIC_READ,       1, NULL, 
                                    OPEN_EXISTING,     FILE_ATTRIBUTE_NORMAL, NULL);

    intermediate     = CreateFileA (intermediate_name, GENERIC_WRITE,      0, NULL,
                                    OPEN_ALWAYS,       FILE_ATTRIBUTE_NORMAL, NULL);

    SetFilePointerEx               (src, intToLargeInt(start_index), NULL, FILE_BEGIN);
    for (i = 0; i < BATCHSIZE ; ++i) {
        
        ReadFile                   (src, buffer, BUFFERSIZE, &bytes_read, NULL);
        buffer [BUFFERSIZE - 2]  = '\0';
        if (bytes_read == 0) {
            
            break;
        }
        sscanf                     (buffer, "%lld", &arr[i]);
    }

    QuickSort                      (arr, 0, i - 1);

    for                            (int j = 0; j < i; j++) {

        sprintf                    (buffer, "%lld\r\n", arr[j]);
        WriteFile                  (intermediate, buffer, BUFFERSIZE, &bytes_written, NULL);
    }

    CloseHandle                    (intermediate);
    CloseHandle                    (src);

    return 0;
}
int main ()
{
        HANDLE    src;
        HANDLE    dest;
        char      destination [] = "dest.txt";
        int       size;
        int       no_of_handles;
        HANDLE *  my_thread_handle;
        long long arr[BATCHSIZE];        
        int    *  arr_i;
        HANDLE *  handle_arr;
		bool      b_wait_all;

    src                           = CreateFileA("source.txt", GENERIC_READ, 1, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    dest                          = CreateFileA (destination, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    size                          = GetFileSize (src, NULL);
    no_of_handles                 = ((size + 2) + (BUFFERSIZE * BATCHSIZE - 1)) / (BUFFERSIZE * BATCHSIZE);
    my_thread_handle              = new HANDLE [no_of_handles];
    arr_i                         = new int [no_of_handles];
    
    for (int i = 0; i < no_of_handles; ++i) {
        
        arr_i [i]                 = i;
        my_thread_handle [i]      = CreateThread(NULL, 0, mythread, &arr_i[i], NULL, NULL);
		if (my_thread_handle [i] == 0) {
			
			printf ("\nThread Creation Failed. Exiting");
			return 1;
		}
    }
    
    WaitForMultipleObjects          (no_of_handles, my_thread_handle, b_wait_all, INFINITE);
    
    handle_arr                    = (HANDLE *) malloc ((no_of_handles) * sizeof(HANDLE));
    for (int i = 0; i < no_of_handles; ++i) {

            char path [20];

        sprintf                     (path, "%d.txt", i + 1);
        handle_arr [i]            = CreateFileA (path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    }

    MergeSortedFiles                (handle_arr, no_of_handles, dest);

    for (int i = 0; i < no_of_handles; i++) {

        CloseHandle                 (handle_arr[i]);
    }
    free                            (handle_arr);
    CloseHandle                     (src);
    CloseHandle                     (dest);
    for (int i = 0; i < no_of_handles; ++i) {
        
        CloseHandle                 (my_thread_handle [i]);
    }
    delete                       [] arr_i;
    delete                       [] my_thread_handle;
    return 0;
}

