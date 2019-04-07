#ifndef MEM_H
#define MEM_H

#include "../cpu/type.h"

// Copies the memory from source to destination. See memcpy docs.
void memory_copy(char *source, char *dest, int nbytes);

// Sets the val to memory address range [dest, dest + len).
void memory_set(u8 *dest, u8 val, u32 len);

// Returns a pointer to a free memory with the specified number of bytes ('size')
// as well as the corresponding physical address.
// If align is true, then the pages are aligned to 4K or 0x1000.
u32 kmalloc(u32 size, int align, u32 *phys_addr);
// TODO: implement free.

#endif
