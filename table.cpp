#include "table.h"
#include "types.h"

instruction_type instruction_table[256];

void init_instruction_table()
{
    for (int i = 0; i < 256; i++)
    {
        instruction_table[i] = {Instruction_None, {}};
    }
    // Statically assign first byte values to instructions.
    //
    // Register/memory to/ from register
    instruction_table[0b10001000] = {Instruction_Mov, Mov_Standard};
    instruction_table[0b10001001] = {Instruction_Mov, Mov_Standard};
    instruction_table[0b10001010] = {Instruction_Mov, Mov_Standard};
    instruction_table[0b10001011] = {Instruction_Mov, Mov_Standard};

    // Immediate to Register/Memory
    instruction_table[0b11000110] = {Instruction_Mov, Mov_Immediate};
    instruction_table[0b11000111] = {Instruction_Mov, Mov_Immediate};

    // Immediate to reg movs
    instruction_table[0b10110000] = {Instruction_Mov, Mov_Immediate_Reg};
    instruction_table[0b10110001] = {Instruction_Mov, Mov_Immediate_Reg};
    instruction_table[0b10110010] = {Instruction_Mov, Mov_Immediate_Reg};
    instruction_table[0b10110011] = {Instruction_Mov, Mov_Immediate_Reg};
    instruction_table[0b10110100] = {Instruction_Mov, Mov_Immediate_Reg};
    instruction_table[0b10110101] = {Instruction_Mov, Mov_Immediate_Reg};
    instruction_table[0b10110110] = {Instruction_Mov, Mov_Immediate_Reg};
    instruction_table[0b10110111] = {Instruction_Mov, Mov_Immediate_Reg};

    instruction_table[0b10111000] = {Instruction_Mov, Mov_Immediate_Reg};
    instruction_table[0b10111001] = {Instruction_Mov, Mov_Immediate_Reg};
    instruction_table[0b10111010] = {Instruction_Mov, Mov_Immediate_Reg};
    instruction_table[0b10111011] = {Instruction_Mov, Mov_Immediate_Reg};
    instruction_table[0b10111100] = {Instruction_Mov, Mov_Immediate_Reg};
    instruction_table[0b10111101] = {Instruction_Mov, Mov_Immediate_Reg};
    instruction_table[0b10111110] = {Instruction_Mov, Mov_Immediate_Reg};
    instruction_table[0b10111111] = {Instruction_Mov, Mov_Immediate_Reg};

    // Memory to accumulator
    instruction_table[0b10100000] = {Instruction_Mov, Mov_Mem_Accum};
    instruction_table[0b10100001] = {Instruction_Mov, Mov_Mem_Accum};

    // Accumulator to memory
    instruction_table[0b10100010] = {Instruction_Mov, Mov_Accum_Mem};
    instruction_table[0b10100011] = {Instruction_Mov, Mov_Accum_Mem};

    // Register/Memory to segment register
    instruction_table[0b10001110] = {Instruction_Mov, Mov_Segment_Reg};
    instruction_table[0b10001100] = {Instruction_Mov, Mov_Segment_Reg};

    // TODO(Nate): Add add instructions
    // TODO(Nate): Add sub instructions
    // TODO(Nate): Add cmp instructions
    // TODO(Nate): Add jnz instructions
    // instructions?
}
