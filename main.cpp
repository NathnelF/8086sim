#include "file.h"
#include <stdio.h>

/*

  We need to load binary data from file
  Parse first byte for possible instruction types
  Parse variable fields based on instruction type
  Generate operands from those fields
  Store instruction type and operands in a struct
  Print and format the information in the instruction struct.




*/

// TODO(Nate): add register enumeration (ability to show wide (ax) and (ah vs al))

// TODO(Nate): add effective address (register + register + immediate) (with option for 0 on all three)

enum instruction_type
{
    Instruction_None,
    Instruction_Mov,
};

enum operand_type
{
    Operand_None,
    Operand_Register,
};

struct instruction_operands
{
    operand_type Type;
    union {
        int register_index;
        char *effective_addres;
        unsigned int immediate;
    };
};

struct instruction
{
    instruction_type Type;
    instruction_operands Operands[2];
    unsigned char Length;
};

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
    printf("Filename: %s, file length: %d\n", binary_filename,
           binary_filelength);
    for (int i = 0; i < binary_filelength; i++)
    {
      print_byte(file_data[i]);
    }
    puts("");
    return 0;
}
