mov ah, 0x0e ; tty mode

mov bp, 0x8000 ; this is an address far away from 0x7c00 so that we don't get overwritten
mov sp, bp ; if the stack is empty then sp points to bp

push 'A'
push 'B'
push 'C'

; to show how the stack gros downward
mov al, [0x7ffe] ; 0x8000 - 2
int 0x10

; however, don't try to access [0x8000] now, because it won't work
; BP points to 0x8000 but there is no valid data at that address
; and pushing data on the stack always moves the SP first and then inserts the data
; on the new address
mov al, [0x8000]
int 0x10

; so we expect to have B at 0x7ffc and C at 0x7ffa
mov al, [0x7ffc] ; Print B
int 0x10

mov al, [0x7ffa] ; Print A
int 0x10

; recover our characters using the standard procedure: 'pop'
; We can only pop full workds so we need an auxiliary register to manipulate
; the lower byte
pop bx
mov al, bl
int 0x10 ; Prints C

pop bx
mov al, bl
int 0x10 ; Prints B

pop bx
mov al, bl
int 0x10 ; Prints A

; data that has been pop'd from the stack is garbage now
mov al, [0x8000]
int 0x10

jmp $
times 510-($-$$) db 0
dw 0xaa55
