
org 0x7c00

bits 16 

%define BOOTLOADER 1
%include "variables.asm"

start: 
    jmp main 

main: 

    mov cx, 5

bucle_inicio: 

    mov si, linea_nueva
    call imprimir_cadena
    loop bucle_inicio

    mov si, mensaje_bienvenida
    call imprimir_cadena 
    
    mov si, linea_nueva
    call imprimir_caracter

    mov cx, 20

bucle_inicio2: 

    mov si, linea_nueva
    call imprimir_cadena 
    loop bucle_inicio2

    jmp $

times 510-($-$$) db 0 
dw 0xAA55 


