
org 0x7c00

bits 16 

start: 
    jmp main 

main:  

    mov si, mensaje_bienvenida
    call imprimir_cadena 
    
    mov si, linea_nueva
    call imprimir_cadena 

    mov si, mensaje_prompt 
    call imprimir_cadena 
    
    mov si, linea_nueva  
    call imprimir_cadena 

    call leer_caracter
    mov al, [char] 
    call imprimir_caracter 

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

leer_caracter:

    mov ah, 0
    int 0x16 
    mov [char], al 
    ret

;Variables

mensaje_bienvenida db "DarioAleproyecto", 0 
mensaje_prompt db "DarioAleproyecto", 0
mensaje_caracter_introducido db "Has presionado la tecla: ", 0
char db 0x00, 0 
linea_nueva db 0x0D, 0x0A, 0 


times 510-($-$$) db 0 
dw 0xAA55 
