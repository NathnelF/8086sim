#pragma once

#include "types.h"

instruction_type get_instruction_type(unsigned char byte);

void print_instruction(instruction_type instruction_val);

void print_move_type(int type);

int length_from_mod(unsigned char byte);

// TODO(Nate): handle specific mov types.
int get_mov_instruction_length(unsigned char *memory, int memory_length,
                               int &memory_position, instruction_type inst);

instruction decode_instruction(unsigned char *memory, int memory_length,
                               int &memory_position, instruction_type inst_type,
                               int instruction_length);
