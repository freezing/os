#include "../drivers/port.h"

#define COLOR 0x0f
#define ANOTHER_COLOR 0xf0

void draw(const char color) {
  char* video_memory = (char*) 0xb8000;
  char* s = "From C code changed video memory text.";
  char* c = s;
  while (*c != '.') {
    *video_memory = *c;
    video_memory[1] = color;
    video_memory += 2;
    c++;
  }
}

void draw_forever() {
  int color = COLOR;
  while (1) {
    draw(color);
    if (color == COLOR) {
      color = ANOTHER_COLOR;
    }
    else {
      color = COLOR;
    }
  }
}

void query_cursor() { 
  // Screen cursor position: ask VGA control register (0x3d4) for bytes;
  // 14 = high byte of cursor and 15 = low byte of cursor.
  
  // Request byte 14: high byte of cursor position.
  write_byte_to_port(0x3d4, 14);
  // Data is returned in VGA data register (0x3d5).
  int position = read_byte_from_port(0x3d5);
  position = position << 8;

  // Request the low byte.
  write_byte_to_port(0x3d4, 15);
  position += read_byte_from_port(0x3d5);

  // VGA 'cells' consist of the character and its control data
  // e.g. 'white on black background', 'red text on white bg', etc.
  int offset_from_vga = position * 2;

  // Now we can examine both variables using gdb, since we will
  // don't know how to print strings on screen. Run 'make debug' and
  // on the gdb console:
  // b kernel.c:50
  // continue
  // print position
  // print offset_from_vga

  // Let's write on the current cursor position.
  char *vga = 0xb8000;
  vga[offset_from_vga] = 'X';
  vga[offset_from_vga+1] = COLOR;
}

void query_cursor_forever() {
  while (1) {
    query_cursor();
  }
}

void main() {
  // draw_forever();
  query_cursor_forever();
}
