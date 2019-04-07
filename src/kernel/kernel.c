
void keyboard_input(char* input) {

}

void main() {
  isr_install();
  irq_install(keyboard_input);
}
