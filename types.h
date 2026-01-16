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
    operand_type type;
    union {
        int register_index;
        char *effective_addres;
        unsigned int immediate;
    };
};

struct instruction
{
    instruction_type type;
    instruction_operands operands[2];
    unsigned char length;
};
