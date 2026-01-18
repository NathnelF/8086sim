#pragma once

#include "table.h"
#include "types.h"

instruction_type get_instruction_type(unsigned char byte);

void print_instruction(instruction_type instruction_val);

void print_move_type(int type);

// TODO(Nate): handle specific mov types.
