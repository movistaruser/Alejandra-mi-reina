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
leer_caracter: ; Función para leer un caracter

    mov ah, 0 ; Asignamos a ah el valor 0, que es la función para leer un caracter
    int 0x16 ; Interrupcion de BIOS para leer caracter
    mov [char], al ; Movemos lo que hay almacenado en el registro al la variable char (El caracter)
    ret

;Variables

mensaje_bienvenida db "Loading Alejandra mi reina...", 0 
char db 0x00, 0 
linea_nueva db 0x0D, 0x0A, 0
mensaje_kernel db "Pulsa cualquier tecla para cargar..."