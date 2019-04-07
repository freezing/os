#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "../libc/string.h"
#include "../libc/mem.h"

#include <stdint.h>

void run_kmalloc_test() {
  uint32_t phys_addr;
  uint32_t page = kmalloc(1000, 1, &phys_addr);
  char page_str[16] = "";
  hex_to_ascii(page, page_str);
  char phys_str[16] = "";
  hex_to_ascii(phys_addr, phys_str);
  kprint("Page: ");
  kprint(page_str);
  kprint(", physical address: ");
  kprint(phys_str);
  kprint("\n");
}

void on_keyboard_input_changed(char* input) {
  if (strcmp(input, "END") == 0) {
    kprint("Stopping the CPU. Bye!\n");
    asm volatile("hlt");
  } else if (strcmp(input, "PAGE") == 0) {
    // Code to test kmalloc, the rest is unchanged.
    run_kmalloc_test();
  }

  kprint("You said: ");
  kprint(input);
  kprint("\n");
}

void run_shell() {
  kprint("Type something, it will go through the kernel\n"
        "Type END to halt the CPU or PAGE to request a kmalloc()\n> ");
  // TODO: Ideally, shell would register the IRQ listener for keyboard here.
}

void kernel_main() {
  isr_install();
  irq_install(on_keyboard_input_changed);
  run_shell();
}
