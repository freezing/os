/* This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 */
void dummy_test_entrypoint() {
  
}

const char COLOR = 0x0f;

void main() {
  char* video_memory = (char*) 0xb8000;
  char* s = "From C code changed video memory text.";
  char* c = s;
  while (*c != '.') {
    *video_memory = *c;
    video_memory[1] = COLOR;
    video_memory += 2;
    c++;
  }
}
