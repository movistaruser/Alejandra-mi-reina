

; funciones comparar comandos




section .text
global comparar_comando

comparar_comando:
    call comparar_comando_codigo
    ret

comparar_comando_codigo:
    mov si, buffer_shell
    mov di, cadena_clear

    call comparar_cadena

    cmp al, 1
    je clear

    mov si, buffer_shell
    mov di, cadena_hola

    call comparar_cadena

    cmp al, 1
    je hola

    mov si, buffer_shell
    mov di, cadena_green
    
    call comparar_cadena

    cmp al, 1
    je green

    
    mov si, buffer_shell
    mov di, cadena_blue
    
    call comparar_cadena

    cmp al, 1
    je blue

    
    mov si, buffer_shell
    mov di, cadena_red
    
    call comparar_cadena

    cmp al, 1
    je red

    
    mov si, buffer_shell
    mov di, cadena_color
    
    call comparar_cadena

    cmp al, 1
    je color
    
    mov si, buffer_shell
    mov di, cadena_time
    
    call comparar_cadena

    cmp al, 1
    je time
        
    mov si, buffer_shell
    mov di, cadena_date
    
    call comparar_cadena

    cmp al, 1
    je date
    
    mov si, buffer_shell
    mov di, cadena_age
    
    call comparar_cadena

    cmp al, 1
    je age

    mov si, buffer_shell
    mov di, cadena_shutdown
    
    call comparar_cadena

    cmp al, 1
    je shutdown

    jmp error_comando

    jmp shell
comparar_cadena:
    mov al, [si]
    mov bl, [di]

    cmp al, bl
    jne no_es_igual

    cmp al, 0         ; ¿Llegamos al final de ambas cadenas?
    je es_igual

    inc si
    inc di
    jmp comparar_cadena

es_igual:

call limpiar_buffer
    mov al, 1
    ret

no_es_igual:
    mov al, 0
    ret


error_comando:

    
    mov si, mensaje_error
    call imprimir_cadena

    mov si, buffer_shell
    call imprimir_cadena

    ret

; -----------------------------------------------

; funciones shell

limpiar_pantalla:

    mov ah, 0x06        ; función de scroll up
    mov al, 0           ; 0 = limpiar toda la pantalla
    mov bh, 0x7
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

    cmp dl, 7            ; Evitar borrar el prompt
    jbe shell            ; Si está muy a la izquierda, no borrar

    dec dl               ; Retroceder una columna

    ; Calcular dirección de memoria de video
    mov ax, 0xB800
    mov es, ax

    movzx si, dh         ; Fila
    imul si, 80          ; si = fila * 80
    movzx di, dl         ; Columna
    add si, di
    shl si, 1            ; Cada carácter ocupa 2 bytes

    ; Borrar carácter en pantalla
    mov byte [es:si], ' '
    mov byte [es:si + 1], 0x07

    ; Mover cursor hacia atrás
    mov ah, 0x02
    mov bh, 0x00
    mov dh, dh
    mov dl, dl
    int 0x10

    ; Borrar del buffer
    cmp bx, 0
    je shell
    dec bx
    mov byte [buffer_shell + bx], 0

    jmp shell


enter_shell:
    mov ah, 0x03
    mov bh, 0x00
    int 0x10

    inc dh
    mov dl, 7

    cmp dh, 24
    ja scroll_shell

    mov ah, 0x02
    mov bh, 0x00
    int 0x10

    mov ah, 0x03
    mov bh, 0x00
    int 0x10

    inc dh
    mov dl, 0

    cmp dh, 24
    ja scroll_shell

    call comparar_comando


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

    call comparar_comando
    cmp al, 1
    je segundo_salto

    mov dh, 24     ; Coloca el cursor en la última línea después del scroll
    mov dl, 0

    mov ah, 0x02
    mov bh, 0x00
    int 0x10

    mov ah, 0x06   ; Función de scroll
    mov al, 1      ; Scroll 1 línea
    mov bh, 0x07   ; Atributo (blanco sobre negro)
    mov cx, 0x0000 ; Esquina superior izquierda
    mov dx, 0x184F ; Esquina inferior derecha (fila 24, col 79)
    int 0x10

    mov dh, 24     ; Coloca el cursor en la última línea después del scroll
    mov dl, 0
    
    jmp segundo_salto

segundo_salto:

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
   
    cmp al, 0x08
    je borrar_caracter

    cmp al, 0x0D
    je enter_shell       
    
    ; Guarda el carácter en el buffer
    mov [buffer_shell + bx], al
    inc bx

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

; ------------------------------------------------------