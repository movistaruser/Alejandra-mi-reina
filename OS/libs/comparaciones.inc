comparar_comando:

    call comparar_comando_codigo

    ret


comparar_comando_codigo

    mov si, buffer_shell     ; Cargar la dirección del buffer
    mov di, cadena_clear     ; Cargar la dirección de la cadena "clear"

    call comparar_cadena       
    je clear

    call error_comando
    call imprimir_cadena
    ret

comparar_cadena:

    mov al, [si]
    mov bl, [di]

    cmp al, bl
    jne error_comando

    cmp al, 0
    je clear

    inc si
    inc di
    jmp comparar_cadena

clear:
    mov si, "clear correcto"
    call imprimir_cadena

    ret

error_comando:

    
    mov si, mensaje_error
    call imprimir_cadena

    mov si, buffer_shell
    call imprimir_cadena

    ret


cadena_clear db "clear", 0