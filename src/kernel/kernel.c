#include "../drivers/screen.h"
#include "util.h"

void fill_screen() {
  int i = 0;
  for (i = 0; i < 24; i++) {
    char str[255];
    int_to_ascii(i, str);
    kprint_at(str, 0, i);
  }
}

void main() {
    clear_screen();
    fill_screen();
    kprint_at("X", 1, 6);
    kprint_at("This text spans multiple lines", 75, 10);
    kprint_at("There is a line\nbreak", 0, 20);
    kprint("There is a line\nbreak");
    kprint_at("What happens when we run out of space?", 45, 24);
}
