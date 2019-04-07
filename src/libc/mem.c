#include "mem.h"

void memory_copy(char *source, char *dest, int nbytes) {
  int i;
  for (i = 0; i < nbytes; i++) {
    dest[i] = source[i];
  }
}

void memory_set(u8 *dest, u8 val, u32 len) {
  u8 *tmp = (u8 *)dest;
  while (len != 0) {
    *tmp = val;
    tmp++;
    len--;
  }
}

// This should be computed at link time, but a hardcoded
// value is fine for now. Remember that our kernel starts
// at 0x1000 as defined on the Makefile.
u32 free_mem_addr = 0x10000;

// Implementation is just a pointer to some free memory that keeps growing.
u32 kmalloc(u32 size, int align, u32 *phys_addr) {
  if (align == 1 && (free_mem_addr & 0xFFFFF000)) {
    free_mem_addr &= 0xFFFFF000;
    free_mem_addr += 0x1000;
  }

  // Save also the physical address.
  if (phys_addr) *phys_addr = free_mem_addr;
  
  u32 ret = free_mem_addr;
  free_mem_addr += size;
  return ret;
}
