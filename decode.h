#pragma once

#include "types.h"

instruction_type get_instruction_type(unsigned char *memory,
                                      int memory_position, int memory_length);

void print_instruction_type(instruction_type instruction_val);

void print_form_type(int type);

void print_instruction_binary(unsigned char *memory, int memory_position,
                              int instruction_length, int memory_length);

int length_from_mod(unsigned char mod, unsigned char rm);

int get_instruction_length(unsigned char *memory, int memory_length,
                           int &memory_position, instruction_type inst);

intermediate_instruction load_instruction_data(unsigned char *memory,
                                               int memory_length,
                                               int &memory_position,
                                               instruction_type inst,
                                               int instruction_length);

operand_type op_from_mod(unsigned char mod);

register_value get_register_value(unsigned char w, unsigned char reg);

effective_address get_effective_address(unsigned char rm, unsigned char disp1,
                                        unsigned char disp2);

instruction decode_instruction_data(unsigned char *memory, int memory_length,
                                    int &memory_position,
                                    intermediate_instruction instruction_data);

void print_operand(instruction_operand op);

// TODO(Nate): Print word / byte when necessary?
// TODO(Nate): Print + 0 on arithmetic instructions when displacement is 0?
void print_instruction(instruction inst);

instruction decode_instruction(unsigned char *memory, int memory_length,
                               int &memory_position);
