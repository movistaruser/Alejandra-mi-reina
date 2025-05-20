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
    ; Cargar el programa desde el sector 2 a la dirección 0x2000
    mov ah, 0x02            ; Función para leer sectores
    mov al, 4               ; Leer 4 sectores (puedes ajustar la cantidad de sectores)
    mov ch, 0               ; Cilindro 0
    mov cl, 2               ; Sector 2
    mov dh, 0               ; Cabeza 0
    mov dl, 0x80            ; Unidad (disco duro)
    mov bx, 0x2000          ; Dirección de carga en 0x2000
    int 0x13                ; Llamada a BIOS para leer los sectores

    jc error_comando        ; Si hay un error, saltar a la rutina de error

    ; Mostrar mensaje en caso de éxito, para asegurarnos de que leemos correctamente
    mov ah, 0x0E            ; Función de escritura de caracteres
    mov al, 'L'             
    int 0x10                ; Mostrar "L" en la pantalla

    ; Realizar un salto largo (far jump) a 0x2000:0x0000
    jmp 0x2000:0x0000       ; Saltar a la dirección 0x2000 donde cargamos el código

error_comando:

    
    mov si, mensaje_error
    call imprimir_cadena

    mov si, buffer_shell
    call imprimir_cadena

    ret


cadena_clear db "clear", 0