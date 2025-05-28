

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
    mov al, 1
    ret

no_es_igual:
    mov al, 0
    ret

clear:

section .text
mov ax, 0x2000
mov es, ax
xor bx, bx

mov ah, 0x02
mov al, 4
mov ch, 0
mov cl, 2
mov dh, 0
mov dl, 0x80
int 0x13


jmp 0x2000:0x0000

hola:

section.text

    mov si, cadena_hola
    call imprimir_cadena

    ret

error_comando:

    
    mov si, mensaje_error
    call imprimir_cadena

    mov si, buffer_shell
    call imprimir_cadena

    ret


cadena_clear db "clear", 0
cadena_hola db "hola", 0