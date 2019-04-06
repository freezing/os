/* This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 */
void dummy_test_entrypoint() {
  
}

const char COLOR = 0x0f;
const char ANOTHER_COLOR = 0xf0;

void draw(const char color) {
  char* video_memory = (char*) 0xb8000;
  char* s = "From C code changed video memory text.";
  char* c = s;
  while (*c != '.') {
    *video_memory = *c;
    video_memory[1] = color;
    video_memory += 2;
    c++;
  }
}

void main() {
  int color = COLOR;
  while (1) {
    draw(color);
    if (color == COLOR) {
      color = ANOTHER_COLOR;
    }
    else {
      color = COLOR;
    }
  }
}
