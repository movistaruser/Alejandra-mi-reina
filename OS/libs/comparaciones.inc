comparar_comando:

    call comparar_comando_codigo

    ret


comparar_comando_codigo

    mov si, buffer_shell     ; Cargar la dirección del buffer
    mov di, cadena_clear     ; Cargar la dirección de la cadena "clear"

    call comparar_cadena       

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
jc error_comando

jmp 0x2000:0x0000

error_comando:

    
    mov si, mensaje_error
    call imprimir_cadena

    mov si, buffer_shell
    call imprimir_cadena

    ret


cadena_clear db "clear", 0
cadena_hola db "hola", 0