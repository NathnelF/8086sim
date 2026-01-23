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
    instruction_table[0b10001000] = {Instruction_Mov, Form_Standard};
    instruction_table[0b10001001] = {Instruction_Mov, Form_Standard};
    instruction_table[0b10001010] = {Instruction_Mov, Form_Standard};
    instruction_table[0b10001011] = {Instruction_Mov, Form_Standard};

    // Immediate to Register/Memory
    instruction_table[0b11000110] = {Instruction_Mov, Form_Immediate};
    instruction_table[0b11000111] = {Instruction_Mov, Form_Immediate};

    // Immediate to reg movs
    instruction_table[0b10110000] = {Instruction_Mov, Form_Immediate_Reg};
    instruction_table[0b10110001] = {Instruction_Mov, Form_Immediate_Reg};
    instruction_table[0b10110010] = {Instruction_Mov, Form_Immediate_Reg};
    instruction_table[0b10110011] = {Instruction_Mov, Form_Immediate_Reg};
    instruction_table[0b10110100] = {Instruction_Mov, Form_Immediate_Reg};
    instruction_table[0b10110101] = {Instruction_Mov, Form_Immediate_Reg};
    instruction_table[0b10110110] = {Instruction_Mov, Form_Immediate_Reg};
    instruction_table[0b10110111] = {Instruction_Mov, Form_Immediate_Reg};

    instruction_table[0b10111000] = {Instruction_Mov, Form_Immediate_Reg};
    instruction_table[0b10111001] = {Instruction_Mov, Form_Immediate_Reg};
    instruction_table[0b10111010] = {Instruction_Mov, Form_Immediate_Reg};
    instruction_table[0b10111011] = {Instruction_Mov, Form_Immediate_Reg};
    instruction_table[0b10111100] = {Instruction_Mov, Form_Immediate_Reg};
    instruction_table[0b10111101] = {Instruction_Mov, Form_Immediate_Reg};
    instruction_table[0b10111110] = {Instruction_Mov, Form_Immediate_Reg};
    instruction_table[0b10111111] = {Instruction_Mov, Form_Immediate_Reg};

    // Register/Memory with Register to either
    instruction_table[0b00000000] = {Instruction_Add, Form_Standard};
    instruction_table[0b00000001] = {Instruction_Add, Form_Standard};
    instruction_table[0b00000010] = {Instruction_Add, Form_Standard};
    instruction_table[0b00000011] = {Instruction_Add, Form_Standard};

    // Immediate to Register/Memory
    instruction_table[0b10000000] = {Instruction_Arithmetic,
                                     Form_Immediate_Arithmetic};
    instruction_table[0b10000001] = {Instruction_Arithmetic,
                                     Form_Immediate_Arithmetic};
    instruction_table[0b10000010] = {Instruction_Arithmetic,
                                     Form_Immediate_Arithmetic};
    instruction_table[0b10000011] = {Instruction_Arithmetic,
                                     Form_Immediate_Arithmetic};

    // Immediate to Accumulator
    instruction_table[0b00000100] = {Instruction_Add, Form_Immediate_Accum};
    instruction_table[0b00000101] = {Instruction_Add, Form_Immediate_Accum};

    // Register/Memory and register to either
    instruction_table[0b00101000] = {Instruction_Sub, Form_Standard};
    instruction_table[0b00101001] = {Instruction_Sub, Form_Standard};
    instruction_table[0b00101010] = {Instruction_Sub, Form_Standard};
    instruction_table[0b00101011] = {Instruction_Sub, Form_Standard};

    // Immediate from accumulator
    instruction_table[0b00101100] = {Instruction_Sub, Form_Immediate_Accum};
    instruction_table[0b00101101] = {Instruction_Sub, Form_Immediate_Accum};

    // Register/Memory and register
    instruction_table[0b00111000] = {Instruction_Cmp, Form_Standard};
    instruction_table[0b00111001] = {Instruction_Cmp, Form_Standard};
    instruction_table[0b00111010] = {Instruction_Cmp, Form_Standard};
    instruction_table[0b00111011] = {Instruction_Cmp, Form_Standard};

    // Immediate with accumulator
    instruction_table[0b00111100] = {Instruction_Cmp, Form_Immediate_Accum};
    instruction_table[0b00111101] = {Instruction_Cmp, Form_Immediate_Accum};

    //  TODO(Nate): Add jnz instructions
    //  instructions?
}
