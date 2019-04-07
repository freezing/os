#include "timer.h"
#include "isr.h"
#include "../libc/function.h"

uint32_t tick = 0;

static void timer_callback(registers_t regs) {
  tick++;
  UNUSED(regs);
}

void init_timer(uint32_t freq) {
  // Install the function that will be invoked on each timer interrupt.
  register_interrupt_handler(IRQ0, timer_callback);

  // Get the PIT value: hardware clock at 1193180 Hz.
  // See: https://wiki.osdev.org/Detecting_CPU_Speed
  uint32_t divisor = 1193180 / freq;
  uint8_t low = (uint8_t)(divisor & 0xFF);
  uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);
  // Send the command to request ticks.
  write_byte_to_port(0x43, 0x36);
  write_byte_to_port(0x40, low);
  write_byte_to_port(0x40, high);
}
