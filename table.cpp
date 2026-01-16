#include "table.h"

instruction_type instruction_table[256];

void init_table()
{
    for (int i = 0; i < 256; i++)
    {
        instruction_table[i] = Instruction_None;
    }
    // Statically assign first byte values to instructions.
    // TODO(Nate): Add mov instructions
    // TODO(Nate): Add add instructions
    // TODO(Nate): Add sub instructions
    // TODO(Nate): Add cmp instructions
    // TODO(Nate): Add jnz instructions
    // TODO(Nate): Account for same first byte assigned to multiple instructions?
}
