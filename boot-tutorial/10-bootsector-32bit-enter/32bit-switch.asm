[bits 16]

; To jump into 32-bit mode:
;   1. Disable interrupts
;   2. Load our GDT
;   3. Set a bit on the CPU control register cr0
;   4. Flush the CPU pipeline by issuing a carefully crafted far jump
;   5. Update all the segment registers
;   6. Update the stack
;   7. Call to a well-known label which contains the first useful code in 32 bits

switch_to_pm:
  ; 1. Disable interrupts
  cli
  ; 2. Load the GDT descriptor
  lgdt [gdt_descriptor]
  
  ; 3. Set 32-bit mode bit in cr0
  mov eax, cr0
  or eax, 0x1
  mov cr0, eax

  ; 4. Far jump by using a different segment. This also sets CS to CODE_SEG.
  jmp CODE_SEG:init_pm

[bits 32]
; We are now using 32-bit instructions
init_pm:

; 5. Update the segment registers
  mov ax, DATA_SEG
  mov ds, ax
  mov ss, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  ; 6. Update the stack right at the top of the free space
  mov ebp, 0x90000
  mov esp, ebp

  ; 7. Call a well-known label with useful code
  call BEGIN_PM
