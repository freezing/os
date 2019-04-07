#ifndef UTIL_H
#define UTIL_H

#include "../cpu/types.h"

// Copies the memory from source to destination. See memcpy docs.
void memory_copy(char *source, char *dest, int nbytes);

// Sets the val to memory address range [dest, dest + len).
void memory_set(u8 *dest, u8 val, u32 len);

// Converts integer to ASCII in reversed order.
// This method assumes that the result can fit in the destination array.
void int_to_ascii(int n, char str[]);

// Reverses the specified string in place.
void reverse(char s[]);

// Returns the length of the string.
// Length is defined as the index at which null byte occurs.
// The complexity of this method is O(N), where N is the position of the null byte.
// If null byte doesn't exist, this method will eventually try to access invalid address.
int strlen(char s[]);

#endif
