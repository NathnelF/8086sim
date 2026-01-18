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
    const char *binary_filename = argV[1];
    unsigned char *file_data;
    int binary_filelength = read_file(&file_data, binary_filename);
    if (binary_filelength == -1)
    {
        return -1;
    }
    printf("Filename: %s, file length: %d\n", binary_filename,
           binary_filelength);
    init_all_tables();
    printf("Table sample: %d\n", instruction_table[5]);
    int byte_count = 0;
    for (int i = 0; i < binary_filelength; i++)
    {
        unsigned char current_byte = file_data[i];
        instruction_type inst_type = get_instruction_type(current_byte);
        if (inst_type == 1) //move instruction
        {
            print_instruction(instruction_table[current_byte]);
            printf("\n");

            mov_type move_type = get_move_type(current_byte);
            print_move_type(move_type);
            printf("\n");

            print_byte(current_byte);
            printf("\n");
        }
        byte_count++;
    }
    puts("");
    return 0;
}
