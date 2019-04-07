
void on_keyboard_input_changed(char* input) {
  if (strcmp(input, "END") == 0) {
    kprint("Stopping the CPU. Bye!\n");
    asm volatile("hlt");
  }

  kprint("You said: ");
  kprint(input);
  kprint("\n");
}

void run_shell() {
  kprint("Type something, it will go through the kernel\n"
	"Type END to halt the CPU\n");
  // TODO: Ideally, shell would register the IRQ listener for keyboard here.
}

void main() {
  isr_install();
  irq_install(on_keyboard_input_changed);
  run_shell();
}
