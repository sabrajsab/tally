#include <windows.h>
#include <stdio.h>
#include <strsafe.h>
#define BUFFERSIZE 100

LARGE_INTEGER intToLargeInt(int i) {
    LARGE_INTEGER li;
    li.QuadPart = i;
    return li;
}

int main(int argc, char ** argv)
{
        HANDLE read_file;
        HANDLE write_file;
        DWORD  number_of_bytes_read;
        DWORD  number_of_bytes_written;

    read_file       = CreateFileA (argv [1], GENERIC_READ, FILE_SHARE_READ, NULL,
                                    OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    write_file  = CreateFileA ("dest.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL,
                                    OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    


    if (read_file       == INVALID_HANDLE_VALUE) {
         
        printf ("\nunable to open file \"%s\" for read.\n", argv[1]);
        return 1; 
    }

    if (write_file  == INVALID_HANDLE_VALUE) {
         
        printf ("\nunable to open file \"dest.txt\' for write.\n");
        return 1; 
    }

        char read_write_buffer [BUFFERSIZE];

    while (1) {
        
        if (false == ReadFile(read_file, read_write_buffer, BUFFERSIZE, &number_of_bytes_read, NULL)) {

            printf ("Terminal failure: Unable to read from file\n");
            break;
        }

        if (number_of_bytes_read == 0) {

            printf ("No data left to read from file \n");
            break;
        }

        if(!WriteFile (write_file, read_write_buffer, number_of_bytes_read, &number_of_bytes_written, NULL)) {

            printf ("Error While Writing to File...\n");
        }
		
		SetFilePointerEx(write_file, intToLargeInt(-50), NULL, FILE_CURRENT);
		
    }

    CloseHandle (read_file);
    CloseHandle (write_file);

    system("pause");
    return 0;
}

