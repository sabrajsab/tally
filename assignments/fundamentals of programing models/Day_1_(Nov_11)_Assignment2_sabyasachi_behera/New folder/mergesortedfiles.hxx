#ifndef MERGESORTEDFILES_HXX
#define MERGESORTEDFILES_HXX

#include <stdio.h>
#include <Windows.h>
#define BUFFERSIZE 12

bool IsGreater (char * str1, char * str2) {

    bool flag = true;
    for(int i = 0; 10; ++i) {

        if (str2 [i] > str1 [i]) {

            flag = false;
            break;
        } else if (str1 [i] > str2 [i]) {

            break;
        }
    }
    return flag;
}

int SmallestString (char ** pReadBuffer, int pNoOfFile)
{
    int minn = 0;
    for (int i = 1 ; i < pNoOfFile; ++i) {
        
        if (IsGreater (pReadBuffer [minn], pReadBuffer [i])) {

            minn = i;
        }
    }
    if (pReadBuffer [minn] [0] == 's') {

        return -1;
    }
    return minn;
}

void MergeSortedFiles(HANDLE * pChunkFile, int pNoOfFile, HANDLE pDest)
{
        DWORD  number_of_bytes_read;
        DWORD  number_of_bytes_written;
    char ** read_buffer = (char **) malloc (sizeof (char *) * pNoOfFile);
	for (int i = 0; i < pNoOfFile; ++i) {
		
		read_buffer [i] = (char *) malloc (sizeof (char) * BUFFERSIZE);
	}
    for (int i = 0; i < pNoOfFile; ++i) {

        if (false == ReadFile(pChunkFile [i], read_buffer [i], BUFFERSIZE, &number_of_bytes_read, NULL)) {

            printf ("Terminal failure: Unable to read from file\n");
            return;
        }

        if (number_of_bytes_read == 0) {

            read_buffer [i] [0] = 's';
            break;
        }
    }
    int i;
    while (1) {

        i = SmallestString (read_buffer, pNoOfFile);

        if (i < 0) {

            break;
        }

        if(!WriteFile (pDest, read_buffer [i], BUFFERSIZE, &number_of_bytes_written, NULL)) {

            printf ("Error While Writing to File...\n");
        }

        if (false == ReadFile(pChunkFile [i], read_buffer [i], BUFFERSIZE, &number_of_bytes_read, NULL)) {

            printf ("Terminal failure: Unable to read from file\n");
            return;
        }

        if (number_of_bytes_read == 0) {

            read_buffer [i] [0]= 's';
        }
    }
}

#endif
