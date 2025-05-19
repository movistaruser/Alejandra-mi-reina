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
    cmp bx, 0               ; Si BX es 0, no hay nada que borrar
    je shell

    ; Decrementar BX para movernos al carácter anterior en el buffer
    dec bx

    ; Borra el carácter de la pantalla (retrocede, imprime espacio, retrocede nuevamente)
    mov ah, 0x0E
    mov al, 0x08            ; Retroceso (carácter)
    int 0x10

    mov al, ' '             ; Espacio en blanco (para borrar el carácter)
    int 0x10

    mov al, 0x08            ; Retroceso nuevamente
    int 0x10

    ; Borra el carácter en el buffer (reemplaza por 0)
    mov byte [buffer_shell + bx], 0
    

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

    mov si, mensaje_error
    call imprimir_cadena

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

    mov si, 0
    call limpiar_buffer
    mov bx, 0

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

    mov si, mensaje_error
    call imprimir_cadena

    mov si, buffer_shell
    call imprimir_cadena


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

    mov si, 0
    call limpiar_buffer
    mov bx, 0

    mov si, Mensaje_shell
    call imprimir_cadena

    jmp shell


section .bss:
    buffer_shell resb 128

leer_comando:

    mov ah, 0
    int 0x16         

    ; Guarda el carácter en el buffer
    mov [buffer_shell + bx], al
    inc bx

    
    cmp al, 0x08
    je borrar_caracter

    cmp al, 0x0D
    je enter_shell       

    ; Imprime el carácter
    mov ah, 0x0E
    int 0x10

    ret

limpiar_buffer:

        mov byte [buffer_shell + si], 0
        inc si
        cmp si, bx
        jl limpiar_buffer
        ret

Mensaje_shell db "DariOS>", 0
mensaje_error db "Error: no se pudo encontrar el comando ", 0