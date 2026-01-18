#include "decode.h"
#include "table.h"
#include "types.h"

instruction_type get_instruction_type(unsigned char byte)
{
    instruction_type type = instruction_table[byte];
    return type;
}

void print_instruction(int instruction_val)
{
    const char *instruction_strings[6] = {
        "None", "Mov", "Add", "Sub", "Cmp", "Jnz",
    };

    printf("%s", instruction_strings[instruction_val]);
}

mov_type get_move_type(unsigned char byte)
{
    mov_type type = mov_table[byte];
    return type;
}

void print_move_type(int type)
{
    const char *mov_type_strings[7] = {"None",
                                       "Standard Mov",
                                       "Immediate to Register or Memory",
                                       "Immediate to Register",
                                       "Accumulator to Memory",
                                       "Memory/Register to Accumulator",
                                       "Segment register to register/memory"};

    printf("%s", mov_type_strings[type]);
}
