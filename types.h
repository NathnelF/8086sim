#pragma once

#include <stdio.h>

enum register_slot
{
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
    bool w; // 0 or 1.
            // Slot 1 w_value = 0 -> AL
            // Slot 1 w_value = 1 -> AX
};

struct effective_address
{
    register_slot slot;
    unsigned short immediate;
};

enum base_instruction
{
    Instruction_None,
    Instruction_Mov,
    Instruction_Add,
    Instruction_Sub,
    Instruction_Cmp,
    Instruction_Jnz,
};

enum mov_type
{
    Mov_None,
    Mov_Standard,
    Mov_Immediate,
    Mov_Immediate_Reg,
    Mov_Mem_Accum,
    Mov_Accum_Mem,
    Mov_Segment_Reg
};

// TODO(Nate): add detailed types for add, sub, cmp, jnz

struct instruction_type
{
    base_instruction base;
    union {
        mov_type move_type;
    };
};

enum operand_type
{
    Operand_None,
    Operand_Register,
    Operand_Memory,
    Operand_Immediate,
};

struct instruction_operand
{
    operand_type type;
    union {
        register_value register_index;
        effective_address address;
        unsigned short immediate;
    };
};

struct intermediate_instruction
{
    instruction_type type;
    int length;
    unsigned char d;
    unsigned char w;
    unsigned char mod;
    unsigned char reg;
    unsigned char rm;
    unsigned char displacement1;
    unsigned char displacement2;
    unsigned char data1;
    unsigned char data2;
};

struct instruction
{
    instruction_type type;
    instruction_operand operands[2];
    int length;
};
