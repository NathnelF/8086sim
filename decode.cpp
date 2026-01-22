#include "decode.h"
#include "file.h"
#include "table.h"
#include "types.h"

instruction_type get_instruction_type(unsigned char byte)
{
    instruction_type type = instruction_table[byte];
    return type;
}

void print_instruction_type(instruction_type instruction_val)
{
    const char *instruction_strings[6] = {
        "None", "Mov", "Add", "Sub", "Cmp", "Jnz",
    };

    printf("%s\n", instruction_strings[instruction_val.base]);
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

    printf("%s\n", mov_type_strings[type]);
}

void print_instruction_binary(unsigned char *memory, int memory_position,
                              int instruction_length, int memory_length)
{
    if (memory_position + instruction_length > memory_length)
    {
        return;
    }
    for (int i = memory_position; i < memory_position + instruction_length; i++)
    {
        print_byte(memory[i]);
    }
    puts("");
    return;
}

int length_from_mod(unsigned char byte)
{
    unsigned char mod = byte >> 6;
    unsigned char rm = byte & ((1 << 3) - 1);
    if (mod == 0b00)
    {
        if (rm == 0b110)
        {
            return 2;
        }
        return 0;
    }
    if (mod == 0b01)
    {
        return 1;
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

operand_type op_from_mod(unsigned char mod)
{
    if (mod == 0b00)
    {
        return Operand_Memory;
    }
    if (mod == 0b01)
    {
        return Operand_Memory;
    }
    if (mod == 0b10)
    {
        return Operand_Memory;
    }
    if (mod == 0b11)
    {
        return Operand_Register;
    }
    printf("Error: unexpected mod value\n");
    return Operand_None;
}

register_value get_register_value(unsigned char w, unsigned char reg)
{
    // printf("w value: %d", w);
    // printf(" reg value: %d", reg);
    // puts("");
    register_value register_val = {};
    if (w == 0b0)
    {
        register_val.w = false;
    }
    else
    {
        register_val.w = true;
    }

    register_slot register_lookup[8] = {
        Register_1, Register_2, Register_3, Register_4,
        Register_5, Register_6, Register_7, Register_8,
    };

    register_val.slot = register_lookup[reg];
    // just lookup reg value and w value
    // sometimes the reg value is reg and sometimes it's r/m
    return register_val;
}

effective_address get_effective_address(unsigned char rm, unsigned char disp1,
                                        unsigned char disp2)
{
    effective_address address = {};
    register_slot register_lookup[8] = {
        Register_1, Register_2, Register_3, Register_4,
        Register_5, Register_6, Register_7, Register_8,
    };

    address.slot = register_lookup[rm];
    address.immediate = disp1 | (disp2 << 8);
    return address;
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
    case Mov_Immediate_Reg: {
        int length = 2; // always at least two
        unsigned char byte1 = memory[memory_position];
        unsigned char w = (byte1 >> 3) & 1;
        if (w == 0b1)
        {
            length += 1;
        }
        return length;
    }
    case Mov_Immediate: {
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

intermediate_instruction load_mov_instruction_data(unsigned char *memory,
                                                   int memory_length,
                                                   int &memory_position,
                                                   instruction_type inst,
                                                   int instruction_length)
{
    intermediate_instruction instruction_data = {};
    instruction_data.type = inst;
    // print_move_type(inst.move_type);
    instruction_data.length = instruction_length;
    if (memory_position + instruction_length > memory_length)
    {
        printf("Error: instruction size exceeds binary memory");
        return instruction_data;
    }
    switch (inst.move_type)
    {
    case Mov_None: {
        instruction_data.type = {Instruction_None, {}};
        return instruction_data;
    }
    case Mov_Standard: {
        instruction_data.type = inst;
        instruction_data.d = memory[memory_position] >> 1 & 1;
        instruction_data.w = memory[memory_position] & 1;

        instruction_data.mod = memory[memory_position + 1] >> 6;
        instruction_data.rm = memory[memory_position + 1] & ((1 << 3) - 1);
        instruction_data.reg =
            (memory[memory_position + 1] >> 3) & ((1 << 3) - 1);

        if (instruction_data.mod == 0b00 && instruction_data.rm == 0b110)
        {
            instruction_data.displacement1 = memory[memory_position + 2];
            instruction_data.displacement2 = memory[memory_position + 3];
        }
        else if (instruction_data.mod == 0b01)
        {
            instruction_data.displacement1 = memory[memory_position + 2];
        }
        else if (instruction_data.mod == 0b10)
        {
            instruction_data.displacement1 = memory[memory_position + 2];
            instruction_data.displacement2 = memory[memory_position + 3];
        }
        return instruction_data;
    }
    case Mov_Immediate_Reg: {
        instruction_data.type = inst;

        instruction_data.w = (memory[memory_position] >> 3) & 1;
        instruction_data.reg = memory[memory_position] & ((1 << 3) - 1);

        instruction_data.data1 = memory[memory_position + 1];

        if (instruction_data.w == 0b1)
        {
            instruction_data.data2 = memory[memory_position + 2];
        }
        return instruction_data;
    }
    case Mov_Immediate: {
        instruction_data.type = inst;
        instruction_data.d = memory[memory_position] >> 1 & 1;
        instruction_data.w = memory[memory_position] & 1;

        instruction_data.mod = memory[memory_position + 1] >> 6;
        instruction_data.rm = memory[memory_position + 1] & ((1 << 3) - 1);
        instruction_data.reg =
            (memory[memory_position + 1] >> 3) & ((1 << 3) - 1);

        // if displacement then bytes 3 and 4 are displace, 5 + 6 are data
        if (instruction_data.mod == 0b01)
        {
            if (instruction_data.rm == 0b110)
            {
                // 16 bit displacement
                instruction_data.displacement1 = memory[memory_position + 2];
                instruction_data.displacement2 = memory[memory_position + 3];
                instruction_data.data1 = memory[memory_position + 4];
                if (instruction_data.w == 0b1)
                {
                    instruction_data.data2 = memory[memory_position + 5];
                }
            }
            // 8 bit displacement
            instruction_data.displacement1 = memory[memory_position + 2];
            instruction_data.data1 = memory[memory_position + 3];
            if (instruction_data.w == 0b1)
            {
                instruction_data.data2 = memory[memory_position + 4];
            }
        }
        if (instruction_data.mod == 0b10)
        {
            // 16 bit displacement
            instruction_data.displacement1 = memory[memory_position + 2];
            instruction_data.displacement2 = memory[memory_position + 3];
            instruction_data.data1 = memory[memory_position + 4];
            if (instruction_data.w == 0b1)
            {
                instruction_data.data2 = memory[memory_position + 5];
            }
        }
        // if no displacement bytes 3 and 4 are data
        if (instruction_data.mod == 0b00 || instruction_data.mod == 0b11)
        {

            instruction_data.data1 = memory[memory_position + 2];
            if (instruction_data.w == 0b1)
            {
                instruction_data.data2 = memory[memory_position + 3];
            }
        }

        return instruction_data;
    }
    case Mov_Mem_Accum: {
        printf("Error: Implement this move type");
        return instruction_data;
    }
    case Mov_Accum_Mem: {
        printf("Error: Implement this move type");
        return instruction_data;
    }
    case Mov_Segment_Reg: {
        printf("Error: Implement this move type");
        return instruction_data;
    }
    }
    printf("Error: This should not happen");
    return instruction_data;
}

instruction decode_mov_instruction(unsigned char *memory, int memory_length,
                                   int &memory_position,
                                   intermediate_instruction instruction_data)
{
    instruction_operand operand1 = {};
    instruction_operand operand2 = {};
    instruction final_instruction = {};
    final_instruction.type = instruction_data.type;
    final_instruction.length = instruction_data.length;
    switch (instruction_data.type.move_type)
    {
    case Mov_None: {
        operand1.type = Operand_None;
        operand2.type = Operand_None;
        final_instruction.operands[0] = operand1;
        final_instruction.operands[1] = operand2;
        return final_instruction;
    }
    case Mov_Standard: {
        // One is reg
        operand1.type = Operand_Register;
        operand1.register_index =
            get_register_value(instruction_data.w, instruction_data.reg);

        //  One is reg/memory
        operand2.type = op_from_mod(instruction_data.mod);

        if (operand2.type == Operand_Register)
        {
            operand2.register_index =
                get_register_value(instruction_data.w, instruction_data.rm);
        }
        if (operand2.type == Operand_Memory)
        {
            operand2.address = get_effective_address(
                instruction_data.rm, instruction_data.displacement1,
                instruction_data.displacement2);
        }

        if (instruction_data.d == 0b1)
        {
            final_instruction.operands[0] = operand1;
            final_instruction.operands[1] = operand2;
        }
        else
        {
            final_instruction.operands[0] = operand2;
            final_instruction.operands[1] = operand1;
        }

        return final_instruction;
    }
    case Mov_Immediate_Reg: {

        // One is reg
        operand1.type = Operand_Register;
        operand1.register_index =
            get_register_value(instruction_data.w, instruction_data.reg);
        // One is immediate
        operand2.type = Operand_Immediate;
        operand2.immediate =
            instruction_data.data1 | (instruction_data.data2 << 8);
        final_instruction.operands[0] = operand1;
        final_instruction.operands[1] = operand2;
        return final_instruction;
    }
    case Mov_Immediate: {
        // One is reg/memory
        operand1.type = op_from_mod(instruction_data.mod);

        if (operand1.type == Operand_Register)
        {
            operand1.register_index =
                get_register_value(instruction_data.w, instruction_data.reg);
        }
        else
        {
            operand1.address = get_effective_address(
                instruction_data.rm, instruction_data.displacement1,
                instruction_data.displacement1);
        }
        // One is immediate
        operand2.type = Operand_Immediate;
        operand2.immediate =
            instruction_data.data1 | (instruction_data.data2 << 8);
        final_instruction.operands[0] = operand1;
        final_instruction.operands[1] = operand2;
        return final_instruction;
    }
    case Mov_Mem_Accum: {
        break;
    }
    case Mov_Accum_Mem: {
        break;
    }
    case Mov_Segment_Reg: {
        break;
    }
    }

    printf("Error: unexpectedly reached end of function\n");
    return final_instruction;
}

void print_operand(instruction_operand op)
{
    const char *register_string_lookup[8][2] = {
        {"al", "ax"}, {"cl", "cx"}, {"dl", "dx"}, {"bl", "bx"},
        {"ah", "sp"}, {"ch", "bp"}, {"dh", "si"}, {"bh", "di"},

    };
    const char *effective_address_string_lookup[8] = {
        "bx + si", "bx + di", "bp + si", "bp + di", "si", "di", "bp", "bx",
    };
    switch (op.type)
    {
    case Operand_None: {
        printf("");
        break;
    }
    case Operand_Register: {
        printf("%s", register_string_lookup[op.register_index.slot]
                                           [op.register_index.w]);
        break;
    }
    case Operand_Memory: {
        if (op.address.immediate)
        {
            printf("[%s + %hu]",
                   effective_address_string_lookup[op.address.slot],
                   op.address.immediate);
        }
        else
        {
            printf("[%s]", effective_address_string_lookup[op.address.slot]);
        }
        break;
    }
    case Operand_Immediate: {
        printf("+ %hu", op.immediate);
        break;
    }
    }
}

void print_mov_instruction(instruction inst)
{
    printf("mov ");
    print_operand(inst.operands[0]);
    printf(", ");
    print_operand(inst.operands[1]);
    printf("\n");
}

instruction decode_instruction(unsigned char *memory, int memory_length,
                               int &memory_position)
{
    instruction final_instruction = {};
    instruction_type inst = get_instruction_type(memory[memory_position]);
    switch (inst.base)
    {
    case Instruction_None: {
        printf("Error: invalid instruction type\n");
        final_instruction.length = memory_length;
        return final_instruction;
    }
    case Instruction_Mov: {
        int instruction_length = get_mov_instruction_length(
            memory, memory_length, memory_position, inst);
        intermediate_instruction instruction_data = load_mov_instruction_data(
            memory, memory_length, memory_position, inst, instruction_length);
        final_instruction = decode_mov_instruction(
            memory, memory_length, memory_position, instruction_data);
        print_mov_instruction(final_instruction);
        // print_instruction_binary(memory, memory_position, instruction_length,
        //                          memory_length);
        break;
    }
    case Instruction_Add: {
        printf("Error: instruction not yet implemented");
        break;
    }
    case Instruction_Cmp: {
        printf("Error: instruction not yet implemented");
        break;
    }
    case Instruction_Sub: {
        printf("Error: instruction not yet implemented");
        break;
    }
    case Instruction_Jnz: {
        printf("Error: instruction not yet implemented");
        break;
    }
    }

    return final_instruction;
}
