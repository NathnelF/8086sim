#include "decode.h"
#include "file.h"
#include "table.h"
#include "types.h"
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
    const char *file_name = argV[1];
    unsigned char *file_data;
    int file_length = read_file(&file_data, file_name);
    if (file_length == -1)
    {
        return -1;
    }
    printf("Filename: %s, file length: %d\n", file_name, file_length);
    init_instruction_table();
    int file_position = 0;
    while (file_position < file_length)
    {
        instruction current_instruction =
            decode_instruction(file_data, file_length, file_position);
        file_position += current_instruction.length;
    }
    for (int i = 0; i < file_length; i++)
    {
    }
    puts("");
    return 0;
}
