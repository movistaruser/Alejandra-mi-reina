
; funciones globales

imprimir_cadena:

    lodsb 
    or al, al 
    jz Fin_de_cadena 
    call imprimir_caracter 
    jmp imprimir_cadena

Fin_de_cadena:

    ret 


imprimir_caracter:
    push ax
    mov ah, 0x0E  
    int 0x10
    pop ax 
    ret
    
leer_caracter: 

    mov ah, 0
    int 0x16 
    mov [char], al 
    ret

ConvertToAscii:
    add al, '0'            ; Convertir el valor numérico a su representación en ASCII
    call imprimir_caracter  ; Llamar a una función para mostrar el carácter en pantalla
    ret

; -------------------------------------------------------------------------