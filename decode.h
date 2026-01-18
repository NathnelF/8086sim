#pragma once

#include "table.h"
#include "types.h"

instruction_type get_instruction_type(unsigned char byte);

void print_instruction(int instruction_val);

mov_type get_move_type(unsigned char byte);

void print_move_type(int type);

// TODO(Nate): handle specific mov types.
