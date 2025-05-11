mov ah, 0x02
mov al, 4
mov ch, 0
mov cl, 2
mov dh, 0
mov bx, 0x1000
int 0x13


jmp 0x1000