#include "string.h"

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

  reverse(str);
}

void reverse(char s[]) {
  int c, i, j;
  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

int strlen(char s[]) {
  int i = 0;
  while (s[i] != '\0') i++;
  return i;
}
