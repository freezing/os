#include "mem.h"

void memory_copy(char *source, char *dest, int nbytes) {
  int i;
  for (i = 0; i < nbytes; i++) {
    dest[i] = source[i];
  }
}

void memory_set(uint8_t *dest, uint8_t val, uint32_t len) {
  uint8_t *tmp = (uint8_t *)dest;
  while (len != 0) {
    *tmp = val;
    tmp++;
    len--;
  }
}

// This should be computed at link time, but a hardcoded
// value is fine for now. Remember that our kernel starts
// at 0x1000 as defined on the Makefile.
uint32_t free_mem_addr = 0x10000;

// Implementation is just a pointer to some free memory that keeps growing.
uint32_t kmalloc(size_t size, int align, uint32_t *phys_addr) {
  if (align == 1 && (free_mem_addr & 0xFFFFF000)) {
    free_mem_addr &= 0xFFFFF000;
    free_mem_addr += 0x1000;
  }

  // Save also the physical address.
  if (phys_addr) *phys_addr = free_mem_addr;
  
  uint32_t ret = free_mem_addr;
  free_mem_addr += size;
  return ret;
}
