limpiar_pantalla:

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

    ret

borrar_caracter:
    ; Obtener posición del cursor
    mov ah, 0x03
    mov bh, 0x00
    int 0x10       ; dh = fila, dl = columna

    cmp dl, 7
    jbe shell      ; Si está en columna 0, no borrar nada

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

enter_shell:
    mov ah, 0x03
    mov bh, 0x00
    int 0x10

    inc dh
    mov dl, 0

    cmp dh, 24
    ja scroll_shell

    mov ah, 0x02
    mov bh, 0x00
    int 0x10
    
    mov si, buffer_shell
    call imprimir_cadena

    mov ah, 0x03
    mov bh, 0x00
    int 0x10

    inc dh
    mov dl, 0

    cmp dh, 24
    ja scroll_shell

    mov ah, 0x02
    mov bh, 0x00
    int 0x10

    mov si, Mensaje_shell
    call imprimir_cadena
    
    jmp shell

scroll_shell:

    mov ah, 0x06   ; Función de scroll
    mov al, 1      ; Scroll 1 línea
    mov bh, 0x07   ; Atributo (blanco sobre negro)
    mov cx, 0x0000 ; Esquina superior izquierda
    mov dx, 0x184F ; Esquina inferior derecha (fila 24, col 79)
    int 0x10

    mov dh, 24     ; Coloca el cursor en la última línea después del scroll
    mov dl, 0

    mov ah, 0x02
    mov bh, 0x00
    int 0x10

    mov si, Mensaje_shell
    call imprimir_cadena

    jmp shell


section .bss:
    buffer_shell resb 128

leer_comando:
    ; Llamar a la función para leer un carácter desde el teclado
    xor si, si
    call leer_caracter_comando

    cmp si, 127
    je enter_shell

    ; Comparar si el carácter leído es un salto de línea (Enter)
    cmp al, 0x0D  ; Compara con el valor de Enter (0x0D)
    je final_comando

    ; Almacenar el carácter en el buffer
    mov [buffer_shell + si], al
    inc si

    call imprimir_caracter

    jmp leer_comando

final_comando:

    mov byte [buffer_shell + si], 0
    ret

leer_caracter_comando:
    ; Leer un carácter desde el teclado con interrupción 0x16
    mov ah, 0   ; Función 0: leer un carácter del teclado
    int 0x16    ; Interrupción para leer del teclado
    ret

Mensaje_shell db "DariOS>", 0