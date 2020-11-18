#include <windows.h>
#include <stdio.h>
#include <strsafe.h>
#define BLOCKSIZE 10


LARGE_INTEGER intToLargeInt(int i) {
    LARGE_INTEGER li;
    li.QuadPart = i;
    return li;
}

void pad (char * pStr)
{
	int i = 1;
	for (; i < BLOCKSIZE; ++i) {

		if(pStr[i] == '\0') {
			
			break;
		}
	}
	
	for (; i < BLOCKSIZE; ++i) {
		
		pStr [i] = '_';
	}
	pStr [BLOCKSIZE - 1] = '\n';
	pStr [BLOCKSIZE - 2] = '\r';
}


int main(int argc, char ** argv)
{
        HANDLE write_file;
        DWORD  number_of_bytes_read;
        DWORD  number_of_bytes_written;
		char read_write_buffer [BLOCKSIZE];
		int counter = 0;

    write_file  = CreateFileA ("dest.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL,
                                    OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (write_file  == INVALID_HANDLE_VALUE) {
         
        printf ("\nunable to open file \"dest.txt\' for write.\n");
        return 1; 
    }

        

    SetFilePointerEx(write_file, intToLargeInt(0), NULL, FILE_BEGIN);
    while (!LockFile (write_file, 0, 0, 1, 0));
    if (false == ReadFile(write_file, read_write_buffer, BLOCKSIZE, &number_of_bytes_read, NULL)) {

        printf ("1Terminal failure: Unable to read from file\n");
        return 1;
    }

	if (number_of_bytes_read == 0) {

		
		sprintf (read_write_buffer, "%d", counter);
		pad (read_write_buffer);
		
		if(!WriteFile (write_file, read_write_buffer, BLOCKSIZE, &number_of_bytes_written, NULL)) {

			printf ("Error While Writing to File...\n");
		}
		
		if(!WriteFile (write_file, read_write_buffer, BLOCKSIZE, &number_of_bytes_written, NULL)) {

			printf ("Error While Writing to File...\n");
		}
	}
    UnlockFile (write_file, 0, 0, 1, 0);
    while (counter < 100000) {
        
        if (!LockFile (write_file, 0, 0, 1, 0)) {
				
			continue;
		}

        SetFilePointerEx(write_file, intToLargeInt(0), NULL, FILE_BEGIN);
        if (false == ReadFile(write_file, read_write_buffer, BLOCKSIZE, &number_of_bytes_read, NULL)) {

            printf ("2Terminal failure: Unable to read from file\n");
            break;
        }
		sscanf (read_write_buffer, "%d", &counter);
		
		
		
		SetFilePointerEx(write_file, intToLargeInt(0), NULL, FILE_END);
		
		sprintf (read_write_buffer, "A%d", counter);
		pad (read_write_buffer);
		
		if(!WriteFile (write_file, read_write_buffer, BLOCKSIZE, &number_of_bytes_written, NULL)) {

			printf ("Error While Writing to File...\n");
		}
		counter ++;
		sprintf (read_write_buffer, "%d", counter);
		
		pad (read_write_buffer);
		
		SetFilePointerEx(write_file, intToLargeInt(0), NULL, FILE_BEGIN);
		if(!WriteFile (write_file, read_write_buffer, BLOCKSIZE, &number_of_bytes_written, NULL)) {

			printf ("Error While Writing to File...\n");
		}
		UnlockFile (write_file, 0, 0, 1, 0);
	}	
    CloseHandle (write_file);

    system("pause");
    return 0;
}
