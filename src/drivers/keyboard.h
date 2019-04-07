#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../cpu/types.h"

// Initializes the keyboard and registers the keyboard callback
// that is invoked on each ENTER key pressed with the data
// on the line.
void init_keyboard(void (*keyboard_callback)(char *input));

#endif
