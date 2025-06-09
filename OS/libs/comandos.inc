clear:

    mov ah, 0x06        ; función de scroll up
    mov al, 0  
    mov bh, [color_actual]       
    mov cx, 0x0000      ; esquina superior izquierda (fila 0, columna 0)
    mov dx, 0x184F      ; esquina inferior derecha (fila 24, columna 79)
    int 0x10

    
    mov ah, 0x02        ; función de mover cursor
    mov bh, 0x00        ; página 0
    mov dh, 0x00        ; fila 0
    mov dl, 0x00        ; columna 0
    int 0x10

    xor bx, bx            ; Reiniciar índice del buffer
    mov si, 0
    call limpiar_buffer   ; Limpiar contenido del buffer



    jmp inicio
 

hola:

    call limpiar_buffer
    mov si, cadena_hola
    call imprimir_cadena


    ret

green:

    mov byte [color_actual], 0x02


    mov ah, 0x06        ; función de scroll up
    mov al, 0           ; 0 = limpiar toda la pantalla
    mov bh, [color_actual]    ; atributo: fondo negro, texto gris claro (07h)
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

    mov byte [color_actual], 0x01

    mov ah, 0x06        ; función de scroll up
    mov al, 0           ; 0 = limpiar toda la pantalla
    mov bh, [color_actual]      ; atributo: fondo negro, texto gris claro (07h)
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

    mov byte [color_actual], 0x04

    mov ah, 0x06        ; función de scroll up
    mov al, 0           ; 0 = limpiar toda la pantalla
    mov bh, [color_actual]      ; atributo: fondo negro, texto gris claro (07h)
    mov cx, 0x0000      ; esquina superior izquierda (fila 0, columna 0)
    mov dx, 0x184F      ; esquina inferior derecha (fila 24, columna 79)
    int 0x10


    mov ah, 0x02        ; función de mover cursor
    mov bh, 0x00        ; página 0
    mov dh, 0x00        ; fila 0
    mov dl, 0x00        ; columna 0
    int 0x10

    ret


reset:

    mov byte [color_actual], 0x07

    mov ah, 0x06        ; función de scroll up
    mov al, 0           ; 0 = limpiar toda la pantalla
    mov bh, [color_actual]      ; atributo: fondo negro, texto gris claro (07h)
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

    push ax
    push bx
    push cx
    push dx


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


    pop dx
    pop cx
    pop bx
    pop ax

    ret

date:

    push ax
    push bx
    push cx
    push dx


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
    mov al, ch          
    shr al, 4
    add al, 30h
    call imprimir_caracter

    mov al, ch           
    and al, 0x0F
    add al, 30h
    call imprimir_caracter

    pop dx
    pop cx
    pop bx
    pop ax

    ret


age:



 mov si, age_int
call imprimir_cadena           ; Imprime "age_int"

mov ah, 0
int 0x16                       ; Lee una tecla (teclado)
mov [age_var1], al             ; Almacena el primer carácter en age_var1

mov al, [age_var1]             ; Carga el valor de age_var1 en al
call imprimir_caracter         ; Imprime el primer valor (sin salto de línea adicional)

mov ah, 0
int 0x16                       ; Lee otra tecla (teclado)
mov [age_var2], al             ; Almacena el segundo carácter en age_var2

mov al, [age_var2]             ; Carga el valor de age_var2 en al
call imprimir_caracter         ; Imprime el segundo valor (sin salto de línea adicional)

mov si, age_out
call imprimir_cadena           ; Imprime "age_out"

; Imprime el valor de age_var2
mov al, [age_var2]
call imprimir_caracter         ; Imprime el tercer valor

    ret

shutdown:

    mov ax, 0x5307    ; Función APM para apagar el sistema
    int 0x15          ; Llamar a la interrupción del BIOS para apagar el sistema

    ret

random:
    push ax
    push bx
    push cx
    push dx
    push si

    call _rand         ; genera número aleatorio → AX
    mov bx, ax         ; copiar a BX para no perderlo

    ; convertir a cadena decimal
    mov si, buffer_numero + 5
    mov byte [si], 0   ; terminador nulo

.convierte_digito:
    xor dx, dx
    mov ax, bx
    mov cx, 10
    div cx             ; AX / 10 → cociente en AX, resto en DX
    add dl, '0'        ; convertir dígito a ASCII
    dec si
    mov [si], dl
    mov bx, ax
    cmp bx, 0
    jne .convierte_digito

    ; imprimir la cadena desde si
    call imprimir_cadena

    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    ret