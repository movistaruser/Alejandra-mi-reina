org 0x7c00

bits 16 

start: 
    jmp main 

main: 

    push ax
    push bx
    push cx
    push dx

    mov ah, 0x06       
    mov al, 0           
    mov bh, 0x07    
    mov cx, 0x0000      
    mov dx, 0x184F      
    int 0x10

    mov ah, 0x02       
    mov bh, 0x00    
    mov dh, 0x09      
    mov dl, 0x25       
    int 0x10           

    pop dx
    pop cx
    pop bx
    pop ax

    mov si, mensaje_bienvenida
    call imprimir_cadena

    push ax
    push bx
    push cx
    push dx

    mov ah, 0x02        
    mov bh, 0x00        
    mov dh, 0x0b      
    mov dl, 0x19        
    int 0x10            

    pop dx
    pop cx
    pop bx
    pop ax

    mov si, mensaje_kernel
    call imprimir_cadena

    call leer_caracter
    mov ah, 0x02
    mov al, 4
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov bx, 0x1000
    int 0x13

    jmp 0x1000

    %include "libs/variables.inc"
    %include "libs/funciones_globales.inc"

times 510-($-$$) db 0 
dw 0xAA55 