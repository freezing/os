#include "keyboard.h"
#include "screen.h"
#include "../cpu/port.h"
#include "../cpu/isr.h"
#include "../libc/string.h"
#include "../libc/function.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C

// TODO: This is currently tightly coupled with the caller's callback.
// There can be only one listener to the keyboard events.
// This is not ideal. This should be handeled by the shell code.
static char key_buffer[256];

// See: https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html
// for more details.
#define SC_MAX 57
const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

static void (*kernel_keyboard_callback)(char *input);

static void keyboard_callback_internal(registers_t regs) {
  // The PIC leaves us the scancode in port 0x60.
  uint8_t scancode = read_byte_from_port(0x60);

  if (scancode > SC_MAX) return;
  else if (scancode == BACKSPACE) {
    strbackspace(key_buffer);
    kprint_backspace();
  } else if (scancode == ENTER) {
    kprint("\n");
    // Invoke registered user callback.
    (*kernel_keyboard_callback)(key_buffer);
    key_buffer[0] = '\0';
  } else {
    char letter = sc_ascii[(int)scancode];
    // kprint only accepts char[].
    char str[2] = {letter, '\0'};
    strappend(key_buffer, letter);
    kprint(str);
  }
  UNUSED(regs);
}

void init_keyboard(void (*keyboard_callback)(char *input)) {
  kernel_keyboard_callback = keyboard_callback;
  register_interrupt_handler(IRQ1, keyboard_callback_internal);
}

