#include "file.h"
#include "table.h"
#include <stdio.h>

/*

  We need to load binary data from file -> done
  Parse first byte for possible instruction types
  Parse variable fields based on instruction type
  Generate operands from those fields
  Store instruction type and operands in a struct
  Print and format the information in the instruction struct.




*/
int main(int argC, char **argV)
{
    if (argC != 2)
    {
        printf("Usage: <run> <file>\n");
        return -1;
    }
    const char *binary_filename = argV[1];
    char *file_data;
    int binary_filelength = read_file(&file_data, binary_filename);
    if (binary_filelength == -1)
    {
        return -1;
    }
    // printf("Filename: %s, file length: %d\n", binary_filename, binary_filelength);
    init_table();
    printf("Table sample: %d\n", instruction_table[5]);
    int byte_count = 0;
    for (int i = 0; i < binary_filelength; i++)
    {
        if (byte_count == 0)
        {
            printf("this is the first byte: ");
        }
        print_byte(file_data[i]);
        byte_count++;
    }
    puts("");
    return 0;
}
