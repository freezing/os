#ifndef STRING_H
#define STRING_H

// Converts integer to ASCII.
// This method assumes that the result can fit in the destination array.
void int_to_ascii(int n, char str[]);

// Converts the HEX to ASCII.
// This method assumes that the result can fit in the destination array.
void hex_to_ascii(int hex_number, char str[]);

// Reverses the specified string in place.
void reverse(char s[]);

// Returns the length of the string.
// Length is defined as the index at which null byte occurs.
// The complexity of this method is O(N), where N is the position of the null byte.
// If null byte doesn't exist, this method will eventually try to access invalid address.
int strlen(char s[]);

// Removes the last character from the string.
void strbackspace(char s[]);

// Appends a character c to the string.
void strappend(char s[], char c);

// Compare strings s1 and s2.
// Returns 0 if they are equal.
// Returns a negative number if s1 is lexicographically before s2.
// Returns a position number if s1 is lexicographically after s2.
int strcmp(char s1[], char s2[]);

#endif
