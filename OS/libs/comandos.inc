clear:


    
    mov ah, 0x06        ; función de scroll up
    mov al, 0  
    mov bh, 0x07        ; 0 = limpiar toda la pantalla
    mov cx, 0x0000      ; esquina superior izquierda (fila 0, columna 0)
    mov dx, 0x184F      ; esquina inferior derecha (fila 24, columna 79)
    int 0x10

    
    mov ah, 0x02        ; función de mover cursor
    mov bh, 0x00        ; página 0
    mov dh, 0x00        ; fila 0
    mov dl, 0x00        ; columna 0
    int 0x10

    ret

hola:

    call limpiar_buffer
    mov si, cadena_hola
    call imprimir_cadena

    ret

green:


    mov ah, 0x06        ; función de scroll up
    mov al, 0           ; 0 = limpiar toda la pantalla
    mov bh, 0x02     ; atributo: fondo negro, texto gris claro (07h)
    mov cx, 0x0000      ; esquina superior izquierda (fila 0, columna 0)
    mov dx, 0x184F      ; esquina inferior derecha (fila 24, columna 79)
    int 0x10


    mov ah, 0x02        ; función de mover cursor
    mov bh, 0x00        ; página 0
    mov dh, 0x00        ; fila 0
    mov dl, 0x00        ; columna 0
    int 0x10


    ret

blue:

    mov ah, 0x06        ; función de scroll up
    mov al, 0           ; 0 = limpiar toda la pantalla
    mov bh, 0x01     ; atributo: fondo negro, texto gris claro (07h)
    mov cx, 0x0000      ; esquina superior izquierda (fila 0, columna 0)
    mov dx, 0x184F      ; esquina inferior derecha (fila 24, columna 79)
    int 0x10


    mov ah, 0x02        ; función de mover cursor
    mov bh, 0x00        ; página 0
    mov dh, 0x00        ; fila 0
    mov dl, 0x00        ; columna 0
    int 0x10

    ret

red: 

    mov ah, 0x06        ; función de scroll up
    mov al, 0           ; 0 = limpiar toda la pantalla
    mov bh, 0x04     ; atributo: fondo negro, texto gris claro (07h)
    mov cx, 0x0000      ; esquina superior izquierda (fila 0, columna 0)
    mov dx, 0x184F      ; esquina inferior derecha (fila 24, columna 79)
    int 0x10


    mov ah, 0x02        ; función de mover cursor
    mov bh, 0x00        ; página 0
    mov dh, 0x00        ; fila 0
    mov dl, 0x00        ; columna 0
    int 0x10

    ret

color:

    mov si, color_error
    call imprimir_cadena

    ret
    
time:

    mov ah, 0x02
    int 0x1A

    mov al, ch
    shr al, 4
    add al, 30h
    call imprimir_caracter

    mov al, ch
    and al, 0x0F
    add al, 30h
    call imprimir_caracter

    mov al, ":"
    call imprimir_caracter

    mov al, cl
    shr al, 4
    add al, 30h
    call imprimir_caracter

    mov al, cl
    and al, 0x0F
    add al, 30h
    call imprimir_caracter

    mov al, ":"
    call imprimir_caracter

    mov al, dh
    shr al, 4
    add al, 30h
    call imprimir_caracter

    mov al, dh
    and al, 0x0F
    add al, 30h
    call imprimir_caracter

    ret

date:


    ; Obtener la fecha actual
    mov ah, 0x04         ; Función de BIOS para obtener la fecha
    int 0x1A             ; Llamar a la interrupción 0x1A

    ; Imprimir día
    mov al, dh           ; Decenas del día
    shr al, 4
    add al, 30h
    call imprimir_caracter

    mov al, dh           ; Unidades del día
    and al, 0x0F
    add al, 30h
    call imprimir_caracter

    ; Imprimir "/"
    mov al, "/"
    call imprimir_caracter

    ; Imprimir mes
    mov al, dl           ; Decenas del mes
    shr al, 4
    add al, 30h
    call imprimir_caracter

    mov al, dl           ; Unidades del mes
    and al, 0x0F
    add al, 30h
    call imprimir_caracter

    ; Imprimir "/"
    mov al, "/"
    call imprimir_caracter

    ; Imprimir año
    mov al, ch           ; Decenas del año (por ejemplo, 2023 -> 2)
    shr al, 4
    add al, 30h
    call imprimir_caracter

    mov al, ch           ; Unidades del año (por ejemplo, 2023 -> 3)
    and al, 0x0F
    add al, 30h
    call imprimir_caracter

    ret





cadena_clear db "clear", 0
cadena_hola db "hola", 0
cadena_green db "color green", 0
cadena_color db "color", 0
cadena_blue db "color blue", 0
cadena_red db "color red", 0
cadena_time db "time", 0
cadena_date db "date", 0


color_error db "Sintaxis incorrecta, prueba a poner algun color", 0