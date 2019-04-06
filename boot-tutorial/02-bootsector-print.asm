# Code that prints Hello
mov ah, 0x0e ; go to tty mode
mov al, 'H'
int 0x10 ; general interrupt for video services
mov al, 'e'
int 0x10
mov al, 'l'
int 0x10
int 0x10 ; 'l' is tsill on al
mov al, 'o'
int 0x10

jmp $; jump to the current address = infinite loop

; padding and magic number that flags the file as bootable
times 510 - ($-$$) db 0
dw 0xaa55 
