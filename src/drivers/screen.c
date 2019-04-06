#include "screen.h"
#include "port.h"

// Declaration of private functions.

// Use the VGA ports to get the current cursor position.
int get_cursor_offset();

// Use the VGA ports to set the cursor position.
void set_cursor_offset(int offset);

// Innermost print function for our kernel, directly accesses the video memory.
//
// If col and row are negative, print at the current cursor location.
// If attr is zero, use WHITE_ON_BLACK as default.
// Returns the offset of the next character.
// Sets the video cursor to the returned offset.
int print_char(char c, int col, int row, char attr);

int get_offset(int col, int row);

int get_offset_row(int offset);

int get_offset_col(int offset);

// Implementation of the public kernel API functions.

void clear_screen() {
  int screen_size = MAX_COLS * MAX_ROWS;
  int i;
  char *screen = (char *)VIDEO_ADDRESS;

  for (i = 0; i < screen_size; i++) {
    screen[2 * i] = ' ';
    screen[2 * i + 1] = WHITE_ON_BLACK;
  }
  set_cursor_offset(get_offset(0, 0));
}

void kprint_at(char *message, int col, int row) {
  // Set the cursor if col/row are negative.
  int offset;
  if (col >= row && row >= 0) {
    offset = get_offset(col, row);
  } else {
    offset = get_cursor_offset();
    row = get_offset_row(offset);
    col = get_offset_col(offset);
  }

  // Print the message.
  int i = 0;
  while (message[i] != 0) {
    offset = print_char(message[i], col, row, WHITE_ON_BLACK);
    // Compute row/col for the next iteration.
    row = get_offset_row(offset);
    col = get_offset_col(offset);

    // Next step.
    i++;
  }
}

void kprint(char *message) {
  kprint_at(message, -1, -1);
}

// Implementation of the private kernel functions.

int print_char(char c, int col, int row, char attr) {
  unsigned char *video_memory = (unsigned char*) VIDEO_ADDRESS;
  if (!attr) attr = WHITE_ON_BLACK;

  // Error control: Print a red 'E' if the coords aren't right.
  if (col >= MAX_COLS || row >= MAX_ROWS) {
    video_memory[2 * MAX_COLS * MAX_ROWS - 2] = 'E';
    video_memory[2 * MAX_COLS * MAX_ROWS - 1] = RED_ON_WHITE;
    return get_offset(col, row);
  }

  int offset;
  if (col >= 0 && row >= 0) {
    offset = get_offset(col, row);
  } else {
    offset = get_cursor_offset();
  }

  if (c == '\n') {
    row = get_offset_row(offset);
    offset = get_offset(0, row + 1);
  } else {
    video_memory[offset] = c;
    video_memory[offset + 1] = attr;
    offset += 2;
  }
  set_cursor_offset(offset);
  return offset;
}

int get_cursor_offset() {
  // Ask for high byte of the cursor offset (data 14).
  write_byte_to_port(REG_SCREEN_CTRL, 14);
  // Read high byte.
  int offset = read_byte_from_port(REG_SCREEN_DATA) << 8;

  // Ask for the low byte (data 15).
  write_byte_to_port(REG_SCREEN_CTRL, 15);
  // Read low byte.
  offset += read_byte_from_port(REG_SCREEN_DATA);
  // Return position * size of character cell.
  return offset * 2;
}

void set_cursor_offset(int offset) { 
  // Get actual position by dividing with the cell size.
  offset /= 2;

  // Read the data from the video ports.
  write_byte_to_port(REG_SCREEN_CTRL, 14);
  write_byte_to_port(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
  write_byte_to_port(REG_SCREEN_CTRL, 15);
  write_byte_to_port(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

int get_offset(int col, int row) {
  return 2 * (row * MAX_COLS + col);
}

int get_offset_row(int offset) {
  return offset / MAX_COLS / 2;
}

int get_offset_col(int offset) {
  int row = get_offset_row(offset);
  int screen_width = 2 * MAX_COLS;
  return (offset - row * screen_width) / 2;
}

