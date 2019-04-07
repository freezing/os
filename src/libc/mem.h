#ifndef MEM_H
#define MEM_H

#include <stdint.h>

// Copies the memory from source to destination. See memcpy docs.
void memory_copy(char *source, char *dest, int nbytes);

// Sets the val to memory address range [dest, dest + len).
void memory_set(uint8_t *dest, uint8_t val, uint32_t len);

// Returns a pointer to a free memory with the specified number of bytes ('size')
// as well as the corresponding physical address.
// If align is true, then the pages are aligned to 4K or 0x1000.
uint32_t kmalloc(uint32_t size, int align, uint32_t *phys_addr);
// TODO: implement free.

#endif
