#pragma once

#include "types.h"

instruction_type get_instruction_type(unsigned char byte);

void print_instruction_type(instruction_type instruction_val);

void print_move_type(int type);

void print_instruction_binary(unsigned char *memory, int memory_position,
                              int instruction_length, int memory_length);

int length_from_mod(unsigned char mod, unsigned char rm);

int get_mov_instruction_length(unsigned char *memory, int memory_length,
                               int &memory_position, instruction_type inst);

intermediate_instruction load_mov_instruction_data(unsigned char *memory,
                                                   int memory_length,
                                                   int &memory_position,
                                                   instruction_type inst,
                                                   int instruction_length);

operand_type op_from_mod(unsigned char mod);

register_value get_register_value(unsigned char w, unsigned char reg);

effective_address get_effective_address(unsigned char rm, unsigned char disp1,
                                        unsigned char disp2);

instruction decode_mov_instruction(unsigned char *memory, int memory_length,
                                   int &memory_position,
                                   intermediate_instruction instruction_data);

void print_operand(instruction_operand op);

void print_mov_instruction(instruction inst);

instruction decode_instruction(unsigned char *memory, int memory_length,
                               int &memory_position);

void print_instruction(instruction inst);
