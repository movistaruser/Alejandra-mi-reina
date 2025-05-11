limpiar_pantalla:

    mov ah, 0x06        ; función de scroll up
    mov al, 0           ; 0 = limpiar toda la pantalla
    mov bh, 0x070      ; atributo: fondo negro, texto gris claro (07h)
    mov cx, 0x0000      ; esquina superior izquierda (fila 0, columna 0)
    mov dx, 0x184F      ; esquina inferior derecha (fila 24, columna 79)
    int 0x10


    mov ah, 0x02        ; función de mover cursor
    mov bh, 0x00        ; página 0
    mov dh, 0x00        ; fila 0
    mov dl, 0x00        ; columna 0
    int 0x10

    ret

borrar_caracter:
    ; Obtener posición del cursor
    mov ah, 0x03
    mov bh, 0x00
    int 0x10       ; dh = fila, dl = columna

    cmp dl, 0
    je shell      ; Si está en columna 0, no borrar nada

    dec dl         ; Mover el cursor a la izquierda

    ; Calcular offset en memoria de video
    mov ax, 0xB800
    mov es, ax

    movzx si, dh   ; fila → si
    imul si, 80    ; si = fila * 80
    movzx di, dl   ; columna → di
    add si, di     ; si = fila * 80 + columna
    shl si, 1      ; si = si * 2 (cada carácter ocupa 2 bytes)

    ; Borrar el carácter (poner espacio con atributo blanco)
    mov byte [es:si], ' '
    mov byte [es:si + 1], 0x07

    ; Mover el cursor a la izquierda
    mov ah, 0x02
    mov bh, 0x00
    mov dh, dh
    mov dl, dl
    int 0x10

    jmp shell


Mensaje_shell db "DariOS>", 0