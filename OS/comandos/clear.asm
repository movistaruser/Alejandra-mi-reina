org 0x2000

bits 16 

start:

    mov ah, 0x06        ; función de scroll up
    mov al, 0           ; 0 = limpiar toda la pantalla
    mov bh, 0x07     ; atributo: fondo negro, texto gris claro (07h)
    mov cx, 0x0000      ; esquina superior izquierda (fila 0, columna 0)
    mov dx, 0x184F      ; esquina inferior derecha (fila 24, columna 79)
    int 0x10


    mov ah, 0x02        ; función de mover cursor
    mov bh, 0x00        ; página 0
    mov dh, 0x00        ; fila 0
    mov dl, 0x00        ; columna 0
    int 0x10

    call 0x1000