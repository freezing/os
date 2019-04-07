#include "port.h"

unsigned char read_byte_from_port(unsigned short port) {
  unsigned char result;
  // Inline assembler syntax
  //   Source and destination registers are not the same as in NASM!
  //
  //   '"=a" (result)'; set '=' the C variable '(result)' to the value of register EAX
  //   '"d" (port)': map the C variable '(port)' into EDX register
  //   
  //   Inputs and outputs are separated by colons
  asm("in %%dx, %%al" : "=a" (result) : "d" (port));
  return result;
}

void write_byte_to_port(unsigned short port, unsigned char data) {
  // Both registers are mapped to C variables and
  // nothing is returned, thus, no equals '=' in the asm syntax.
  // However, we see a comma since there are two variables in the input area
  // and none in the 'return' area.
  asm("out %%al, %%dx" : : "a" (data), "d" (port));
}

unsigned short read_word_from_port(unsigned short port) {
  unsigned short result;
  asm("in %%dx, %%ax" : "=a" (result) : "d" (port));
  return result;
}

void write_word_to_port(unsigned short port, unsigned short data) {
  asm("out %%ax, %%dx" : : "a" (data), "d" (port));
}
