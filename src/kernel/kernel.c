#include "../drivers/screen.h"
#include "../drivers/keyboard.h"

#include "util.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "../cpu/timer.h"

void main() {
  isr_install();

  asm volatile("sti");
  // This currently prints every tick, comment so that we can
  // see keyboard events.
  // init_timer(50);
  init_keyboard();
}
