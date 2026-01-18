#pragma once

#include "types.h"

extern instruction_type instruction_table[256];
void init_instruction_table();

extern mov_type mov_table[256];
void init_mov_table();

// TODO(Nate): Add other instruction tables

void init_all_tables();
