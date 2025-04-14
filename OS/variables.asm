%if %defined(BOOTLOADER)
    [org 0x7C00]  ; Direccion para bootloader
%else
    [org 0x1000]  ; Direccion para kernel
%endif

leer_caracter: 

    mov ah, 0 
    int 0x16 
    mov [char], al 
    ret

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

; ------------------------------------------------------------------

mensaje_bienvenida db "Loading Alejandra mi reina...", 0 
char db 0x00, 0 
linea_nueva db 0x0D, 0x0A, 0 