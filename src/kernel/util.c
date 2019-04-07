#include "util.h"

void memory_copy(char *source, char *dest, int nbytes) {
  int i;
  for (i = 0; i < nbytes; i++) {
    dest[i] = source[i];
  }
}

void int_to_ascii(int n, char str[]) {
  int i;
  int sign = n;
  if (sign < 0) {
    n = -n;
  }
  
  i = 0;
  do {
    str[i++] = n % 10 + '0';
    n /= 10;
  } while (n > 0);

  if (sign < 0) str[i++] = '-';
  str[i] = '\0';

  // TODO: Reverse the string.
}
