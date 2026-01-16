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

enum register_slot
{
    Register_None,
    Register_1,
    Register_2,
    Register_3,
    Register_4,
    Register_5,
    Register_6,
    Register_7,
    Register_8,
};

struct register_value
{
    register_slot slot;
    bool w_value; // 0 or 1.
                  // Slot 1 w_value = 0 -> AL
                  // Slot 1 w_value = 1 -> AX
};

struct effective_address
{
    register_value reg1;
    register_value reg2;
    int immediate;
    // reg1.slot = Register_1, reg1.w_value = 1, reg2.slot = Register_none, immediate = 12 -> [AX + 12]
    // reg1.slot = Register_1, reg1.w_value = 1, reg2.slot = Register_2, reg2.w_value = 1 immediate = 12 -> [AX + BX +
    // 12]
};

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
    printf("Filename: %s, file length: %d\n", binary_filename, binary_filelength);
    for (int i = 0; i < binary_filelength; i++)
    {
        print_byte(file_data[i]);
    }
    puts("");
    return 0;
}
