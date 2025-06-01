

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
    
    jmp error_comando

    ret

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





