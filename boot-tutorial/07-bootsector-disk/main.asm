[org 0x7c00]
  mov bp, 0x8000 ; set the stack safely away from us
  mov sp, bp

  mov bx, 0x9000 ; es:bx = 0x0000:0x9000 = 0x09000
  mov dh, 2 ; read 2 sectors
  ; the BIOS sets 'dl' for our boot disk number
  ; if you have trouble, use the 'fda' flag: 'qemu -fda file.bin'
  call disk_load

  mov dx, [0x9000] ; retreive the first lodaded word, 0xdada
  call print_hex
  call print_nl

  mov dx, [0x9000 + 512] ; first word from second loaded sector, 0xFACE
  call print_hex

  jmp $

%include "../05-bootsector-functions-strings/bootsector_print.asm"
%include "../05-bootsector-functions-strings/bootsector_print_hex.asm"
%include "bootsector_disk.asm"

; Magic number
times 510 - ($-$$) db 0
dw 0xAA55

; boot sector = sector 1 of cyl 0 of head 0 of hdd 0
; from now on = sector 2 ...
times 256 dw 0xDADA ; sector 2 = 512 bytes
times 256 dw 0xFACE ; sector 3 = 512 bytes 
