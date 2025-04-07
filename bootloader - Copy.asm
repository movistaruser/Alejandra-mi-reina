
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
    call imprimir_caracter

    mov cx, 20

bucle_inicio2:

    mov si, linea_nueva
    call imprimir_cadena
    loop bucle_inicio2

    jmp $



imprimir_cadena:

    lodsb 
    or al, al 
    jz Fin_de_cadena 
    call imprimir_caracter 
    jmp imprimir_cadena

Fin_de_cadena:

    ret 


imprimir_caracter:

    mov ah, 0x0E  
    int 0x10 
    ret

;Variables

mensaje_bienvenida db "Loading Alejandra mi reina...", 0 
char db 0x00, 0 
linea_nueva db 0x0D, 0x0A, 0 


times 510-($-$$) db 0 
dw 0xAA55 


