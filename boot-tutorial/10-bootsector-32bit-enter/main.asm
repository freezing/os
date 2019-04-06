[org 0x7c00] ; bootloader offset
  mov bp, 0x9000; set the stack
  mov sp, bp

  mov bx, MSG_REAL_MODE
  call print ; this will be written after the BIOS messages

  call switch_to_pm

  ; This will actually never be executed
  mov bx, INTERNAL_ERROR
  call print
  jmp $

%include "../05-bootsector-functions-strings/bootsector_print.asm"
%include "../09-bootsector-32bit-gdt.asm"
%include "../08-bootsector-32bit-print.asm"
%include "32bit-switch.asm"

[bits 32]
BEGIN_PM: ; after the switch we will get here
  mov ebx, MSG_PROT_MODE
  call print_string_pm ; Note that this will be written at the top left corner
  jmp $

MSG_REAL_MODE db "Started in 16-bit real mode", 0
MSG_PROT_MODE db "Loaded 32-bit protected mode", 0
INTERNAL_ERROR db "Reached unexpected instruction. This is a bug!", 0

; bootsector
times 510-($-$$) db 0
dw 0xAA55
