org 0x7c00

bits 16 

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
    call imprimir_cadena

    mov si, mensaje_kernel
    call imprimir_cadena

    mov si, linea_nueva
    call imprimir_cadena
  
    mov cx, 22

bucle_inicio2:

    mov si, linea_nueva
    call imprimir_cadena
    loop bucle_inicio2

    call leer_caracter
    %include "libs/cargar_kernel.inc"


%include "libs/variables.inc"


times 510-($-$$) db 0 
dw 0xAA55 

