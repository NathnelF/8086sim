#include "table.h"

instruction_type instruction_table[256];

void init_instruction_table()
{
    for (int i = 0; i < 256; i++)
    {
        instruction_table[i] = Instruction_None;
    }
    // Statically assign first byte values to instructions.
    //
    // Register/memory to/ from register
    instruction_table[0b10001000] = Instruction_Mov;
    instruction_table[0b10001001] = Instruction_Mov;
    instruction_table[0b10001010] = Instruction_Mov;
    instruction_table[0b10001011] = Instruction_Mov;

    // Immediate to Register/Memory
    instruction_table[0b11000110] = Instruction_Mov;
    instruction_table[0b11000111] = Instruction_Mov;

    // Immediate to reg movs
    instruction_table[0b10110000] = Instruction_Mov;
    instruction_table[0b10110001] = Instruction_Mov;
    instruction_table[0b10110010] = Instruction_Mov;
    instruction_table[0b10110011] = Instruction_Mov;
    instruction_table[0b10110100] = Instruction_Mov;
    instruction_table[0b10110101] = Instruction_Mov;
    instruction_table[0b10110110] = Instruction_Mov;
    instruction_table[0b10110111] = Instruction_Mov;

    instruction_table[0b10111000] = Instruction_Mov;
    instruction_table[0b10111001] = Instruction_Mov;
    instruction_table[0b10111010] = Instruction_Mov;
    instruction_table[0b10111011] = Instruction_Mov;
    instruction_table[0b10111100] = Instruction_Mov;
    instruction_table[0b10111101] = Instruction_Mov;
    instruction_table[0b10111110] = Instruction_Mov;
    instruction_table[0b10111111] = Instruction_Mov;

    // Memory to accumulator
    instruction_table[0b10100000] = Instruction_Mov;
    instruction_table[0b10100001] = Instruction_Mov;

    // Accumulator to memory
    instruction_table[0b10100010] = Instruction_Mov;
    instruction_table[0b10100011] = Instruction_Mov;

    // Register/Memory to segment register
    instruction_table[0b10001110] = Instruction_Mov;
    instruction_table[0b10001100] = Instruction_Mov;

    // TODO(Nate): Add add instructions
    // TODO(Nate): Add sub instructions
    // TODO(Nate): Add cmp instructions
    // TODO(Nate): Add jnz instructions
    // TODO(Nate): Account for same first byte assigned to multiple
    // instructions?
}

mov_type mov_table[256];
void init_mov_table()
{
    for (int i = 0; i < 256; i++)
    {
        mov_table[i] = Mov_None;
    }

    // Register/memory to/ from register
    mov_table[0b10001000] = Mov_Standard;
    mov_table[0b10001001] = Mov_Standard;
    mov_table[0b10001010] = Mov_Standard;
    mov_table[0b10001011] = Mov_Standard;

    // Immediate to Register/Memory
    mov_table[0b11000110] = Mov_Immediate;
    mov_table[0b11000111] = Mov_Immediate;

    // Immediate to reg movs
    mov_table[0b10110000] = Mov_Immediate_Reg;
    mov_table[0b10110001] = Mov_Immediate_Reg;
    mov_table[0b10110010] = Mov_Immediate_Reg;
    mov_table[0b10110011] = Mov_Immediate_Reg;
    mov_table[0b10110100] = Mov_Immediate_Reg;
    mov_table[0b10110101] = Mov_Immediate_Reg;
    mov_table[0b10110110] = Mov_Immediate_Reg;
    mov_table[0b10110111] = Mov_Immediate_Reg;

    mov_table[0b10111000] = Mov_Immediate_Reg;
    mov_table[0b10111001] = Mov_Immediate_Reg;
    mov_table[0b10111010] = Mov_Immediate_Reg;
    mov_table[0b10111011] = Mov_Immediate_Reg;
    mov_table[0b10111100] = Mov_Immediate_Reg;
    mov_table[0b10111101] = Mov_Immediate_Reg;
    mov_table[0b10111110] = Mov_Immediate_Reg;
    mov_table[0b10111111] = Mov_Immediate_Reg;

    // Memory to accumulator
    mov_table[0b10100000] = Mov_Mem_Accum;
    mov_table[0b10100001] = Mov_Mem_Accum;

    // Accumulator to memory
    mov_table[0b10100010] = Mov_Accum_Mem;
    mov_table[0b10100011] = Mov_Accum_Mem;

    // Register/Memory to segment register
    mov_table[0b10001110] = Mov_Segment_Reg;
    mov_table[0b10001100] = Mov_Segment_Reg;
}

void init_all_tables()
{
    init_instruction_table();
    init_mov_table();
    // TODO(Nate): init other instruction tables.
}
