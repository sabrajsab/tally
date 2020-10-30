#include <windows.h>
#include <stdio.h>
#include <strsafe.h>

#define BUFFERSIZE 100

int main(int argc, char ** argv)
{
        HANDLE read_file;
        HANDLE write_num_file;
        HANDLE write_char_file;
        DWORD  number_of_bytes_read;
        DWORD  number_of_bytes_written;
        

    read_file       = CreateFileA (argv [1], GENERIC_READ, FILE_SHARE_READ, NULL,
                                    OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    write_num_file  = CreateFileA("numbers.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL,
                                    OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    write_char_file = CreateFileA ("char.txt", GENERIC_WRITE, FILE_SHARE_READ, NULL,
                                    OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);


    if (read_file       == INVALID_HANDLE_VALUE) {
         
        printf ("\nunable to open file \"%s\" for read or write.\n", argv[1]);
        return 1; 
    }

    if (write_num_file  == INVALID_HANDLE_VALUE) {
         
        printf ("\nunable to open file \"numbers.txt\' for read or write.\n");
        return 1; 
    }

    if (write_char_file == INVALID_HANDLE_VALUE) {
         
        printf ("\nunable to open file \"chars.txt\" for read or write.\n");
        return 1; 
    }
        char read_buffer [BUFFERSIZE];
        char char_buf    [BUFFERSIZE];
        char num_buf     [BUFFERSIZE];
        int    num_itr    {0};
        int    char_itr   {0};

    while (1) {
        
        if (false == ReadFile(read_file, read_buffer, BUFFERSIZE, &number_of_bytes_read, NULL)) {

            printf ("Terminal failure: Unable to read from file\n");
            break;
        }

        if (number_of_bytes_read == 0) {

            printf ("No data left to read from file \n");
            break;
        }

        for (int i = 0; i < number_of_bytes_read; ++i) {
        
            if (read_buffer[i] == '\n' 
                || read_buffer[i] == ' ' 
                || read_buffer[i] == '\t'
                || read_buffer[i] == '\v'
                || read_buffer[i] == '\r') {

                continue;
            }
            if (read_buffer[i] >= '0' && read_buffer[i] <= '9') {

                num_buf [num_itr++] = read_buffer [i];
            } else {

                char_buf [char_itr++] = read_buffer [i];
            }
        }

        if(!WriteFile (write_num_file, num_buf, num_itr, &number_of_bytes_written, NULL)) {

            printf ("Error While Writing to File...\n");
        }

        if(!WriteFile (write_char_file, char_buf, char_itr, &number_of_bytes_written, NULL)) {

            printf ("Error While Writing to File...\n");
        }

        
    }

    CloseHandle (read_file);
    CloseHandle (write_num_file);
    CloseHandle (write_char_file);

    system("pause");
    return 0;
}

