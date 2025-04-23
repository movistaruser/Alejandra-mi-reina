



org 0x7c00

bits 16 

Dir_Kernel	equ	0x1000		;kernel goes into memory at 0x10000
Sectores_Max	equ	15		;kernel is at most 16 sectors (and probably less)
Sector_Inicio	equ	3		;kernel lives at sector 3 (makes room for map & dir)

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

    mov si, Kernel_check
    call imprimir_cadena

    
    mov cx, 22

bucle_inicio2:

    mov si, linea_nueva
    call imprimir_cadena
    loop bucle_inicio2

    call leer_caracter
    %include "cargar_kernel.inc"
	jmp Dir_Kernel:0


%include "variables.inc"




times 510-($-$$) db 0 
dw 0xAA55 

