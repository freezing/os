#ifndef MEM_H
#define MEM_H

#include "../cpu/type.h"

// Copies the memory from source to destination. See memcpy docs.
void memory_copy(char *source, char *dest, int nbytes);

// Sets the val to memory address range [dest, dest + len).
void memory_set(u8 *dest, u8 val, u32 len);

#endif
