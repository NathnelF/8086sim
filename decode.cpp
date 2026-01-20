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

int length_from_mod(unsigned char byte)
{
    // this is the second byte here
    // mod is always high 2 bits
    // r/m is always low 3 bits
    unsigned char mod = byte >> 6;
    unsigned char rm = byte & ((1 << 3) - 1);
    // reg would be (byte >> 3) & ((1 << 3) - 1);
    if (mod == 0b00)
    {
        return 2;
    }
    if (mod == 0b01)
    {
        if (rm == 0b110)
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }
    if (mod == 0b10)
    {
        return 2;
    }
    if (mod == 0b11)
    {
        return 0;
    }
    printf("Error: unexpected mod value\n");
    return 0;
}

int get_mov_instruction_length(unsigned char *memory, int memory_length,
                               int &memory_position, instruction_type inst)
{
    mov_type move_operation = inst.move_type;
    switch (move_operation)
    {
    case Mov_None: {
        return 0;
    }
    case Mov_Standard: {
        int length = 2; // always at least two

        unsigned char byte2 = memory[memory_position + 1];
        length += length_from_mod(byte2);
        return length;
    }
    case Mov_Immediate: {
        int length = 2; // always at least two
        unsigned char byte1 = memory[memory_position];
        unsigned char w = (byte1 >> 3) & 1;
        if (w == 0b1)
        {
            length += 1;
        }
        return length;
    }
    case Mov_Immediate_Reg: {
        int length = 3; // always at least three
        unsigned char byte1 = memory[memory_position];
        unsigned char byte2 = memory[memory_position + 1];
        unsigned char w = (byte1 >> 3) & 1;
        if (w == 0b1)
        {
            length += 1;
        }
        length += length_from_mod(byte2);
        return length;
        break;
    }
    case Mov_Mem_Accum: {
        return -1;
    }
    case Mov_Accum_Mem: {
        return -1;
    }
    case Mov_Segment_Reg: {
        return -1;
    }
    }
    return -1;
}

instruction decode_instruction(unsigned char *memory, int memory_length,
                               int &memory_position, instruction_type inst_type,
                               int instruction_length)
{
    instruction final_instruction = {};
    final_instruction.length = instruction_length;
    final_instruction.type = inst_type;

    // get the operands

    // valid memory is from memory[memory_position] - memory[memory_position +
    // instruction length]

    return final_instruction;
}
