
org 0x7c00

bits 16 

%include "variables.inc"

start: 
    jmp main 

main: 

    mov si, mensaje_bienvenida
    call imprimir_cadena

    jmp $



times 510-($-$$) db 0 
dw 0xAA55 

