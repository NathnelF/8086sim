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
    Instruction_Arithmetic,
};

// For arithmetic instructions
// There are three instructions with the same opcode,
// They are decoded by the middle 3 bits in the second byte
// for these cases we need to check the second bit to deduce the correct form

enum form_type
{
    Form_None,
    Form_Standard,
    Form_Immediate,
    Form_Immediate_Reg,
    Form_Immediate_Accum,
    Form_Immediate_Arithmetic,
};

// TODO(Nate): add detailed types for add, sub, cmp, jnz

struct instruction_type
{
    base_instruction base;
    union {
        form_type form;
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
    unsigned char s;
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
