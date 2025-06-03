org 0x7c00

bits 16 

start: 
    jmp main 

main: 

    push ax
    push bx
    push cx
    push dx


    mov ah, 0x06        ; función de scroll up
    mov al, 0           ; 0 = limpiar toda la pantalla
    mov bh, 0x07     ; atributo: fondo negro, texto gris claro (07h)
    mov cx, 0x0000      ; esquina superior izquierda (fila 0, columna 0)
    mov dx, 0x184F      ; esquina inferior derecha (fila 24, columna 79)
    int 0x10


    mov ah, 0x02        ; función de mover cursor
    mov bh, 0x00        ; página 0
    mov dh, 0x09       ; fila 12 (centro vertical)
    mov dl, 0x25        ; columna 40 (centro horizontal)
    int 0x10            ; llamada a la interrupción del BIOS para mover el 

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

    mov ah, 0x02        ; función de mover cursor
    mov bh, 0x00        ; página 0
    mov dh, 0x0b       ; fila 12 (centro vertical)
    mov dl, 0x19        ; columna 40 (centro horizontal)
    int 0x10            ; llamada a la interrupción del BIOS para mover el 

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