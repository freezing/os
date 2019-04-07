#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xf4

// Screen IO ports.
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

// Public kernel API.

// Clears the screen to the black background.
void clear_screen();

// Print a message on the specified location.
// If col and row are negative, use the current offset.
void kprint_at(char *message, int col, int row);

// Prints the message at the current offset.
void kprint(char *message);

#endif
