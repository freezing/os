global _start
[bits 32]

_start:
  ; Define calling point. Must have the same name as kernel.c 'main' function
  [extern kernel_main] 
  ; Calls the C function. The linker will know where it is placed in memory.
  call kernel_main
  ; Should never happen. Infinite loop.
  jmp $
