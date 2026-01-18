#include "decode.h"
#include "table.h"
#include "types.h"

instruction_type get_instruction_type(unsigned char byte)
{
    instruction_type type = instruction_table[byte];
    return type;
}

void print_instruction(instruction_type instruction_val)
{
    const char *instruction_strings[6] = {
        "None", "Mov", "Add", "Sub", "Cmp", "Jnz",
    };

    printf("%s", instruction_strings[instruction_val.instruction]);
}

void print_move_type(int type)
{

    const char *mov_type_strings[7] = {
        "None",
        "Standard Mov",
        "Immediate to Register/Memory",
        "Immediate to Register",
        "Memory to Accumulator",
        "Accumulator to Memory",
        "Segment Register to Register/Memory",
    };

    printf("%s", mov_type_strings[type]);
}
