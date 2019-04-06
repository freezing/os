[org 0x7c00]
mov ah, 0x0e

# Attempt 1
; Fails because it tries to print the memory address (i.e. pointer)
; not its actual contents
mov al, "1"
int 0x10
mov al, the_secret
int 0x10

# Attempt 2
; Having solved the memory offset problem with 'org', this is now the correct answer.
mov al, "2"
int 0x10
mov al, [the_secret]
int 0x10

# Attempt 3
; As expected, we are adding 0x7c00 twice, so this won't work.
mov al, "3"
int 0x10
mov bx, the_secret
add bx, 0x7c00
mov al, [bx] ; dereference the pointer to get value at [offset + the_secret]
int 0x10

# Attempt 4
; This still works because there are no memory references to pointers, so
; the 'org' mode never applies. Directly addressing meomry by counting bytes
; is always going to work, but it's not practical and it's inconvenient.
mov al, "4"
int 0x10
mov al, [0x7c2b]
int 0x10

the_secret:
  ; ASCII code 0x58 ('X') is stored just before the zero-padding.
  ; On this code that is at byte 0x2d (check it out using 'xxd file.bin')
  db "X"

; zero padding and magic bios number
times 510-($-$$) db 0
dw 0xaa55


