#include "timer.h"
#include "types.h"
#include "../drivers/screen.h"
#include "../kernel/util.h"
#include "isr.h"
#include "../libc/function.h"

u32 tick = 0;

static void timer_callback(registers_t regs) {
  tick++;
  UNUSED(regs);
}

void init_timer(u32 freq) {
  // Install the function that will be invoked on each timer interrupt.
  register_interrupt_handler(IRQ0, timer_callback);

  // Get the PIT value: hardware clock at 1193180 Hz.
  // See: https://wiki.osdev.org/Detecting_CPU_Speed
  u32 divisor = 1193180 / freq;
  u8 low = (u8)(divisor & 0xFF);
  u8 high = (u8)((divisor >> 8) & 0xFF);
  // Send the command to request ticks.
  write_byte_to_port(0x43, 0x36);
  write_byte_to_port(0x40, low);
  write_byte_to_port(0x40, high);
}
