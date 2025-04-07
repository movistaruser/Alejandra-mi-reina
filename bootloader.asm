; Para este proyecto utilizamos nasm (Netwide assembler)


org 0x7c00 ; Es la dirección de la memoria donde la BIOS
; cargará el MBR (Primeros 512 bytes del disco)

bits 16 ; Se carga en modo 16 bits

start:  ; Función, aqui empieza el codigo.
    jmp main ; Salto a la seccion main

main:  ; Función, aqui empieza el codigo principal (Codigo del bootloader)


;Mensaje de bienvenida


    mov si, mensaje_bienvenida ; El registro Si apunta a la variable mensaje_bienvenida (variables definidas despues)
    call imprimir_cadena ; Llamamos a la función que imprime la cadena

; Pasar de linea
    
    mov si, linea_nueva ; Si apunta a la variable linea_nueva 
    call imprimir_cadena ; Llamamos a la funcion imprimir cadena

; Mensaje del prompt

    mov si, mensaje_prompt ; Si apunta a la variable mensaje_prompt
    call imprimir_cadena ; Llamamos a la función que imprime la cadena

; Pasar de linea
    
    mov si, linea_nueva ; Si apunta a la variable linea_nueva 
    call imprimir_cadena ; Llamamos a la funcion imprimir cadena

; Leer un caracter desde el teclado

    call leer_caracter  ; Llamamos a la función leer_caracter

    mov al, [char] ; Cargamos el valor de char, que es un byte, en el registro al
    call imprimir_caracter ; LLamamos a la funcion que imprime el caracter introducido
; Vamos a hacer un bucle de este codigo

    jmp $ ; Esto hace un bucle infinito, con $ salta a la misma direccion de memoria

; Imprimir una cadena terminada en NULL(0x00)

imprimir_cadena: ; Función para imprimir cadena

    lodsb ; Lee caracteres de una cadena de memoria, carga automaticamente el valor del caracter en al
    or al, al ; Hace un or para detectar si al = 0x00
              ; lodsb carga automaticamente el caracter en al
    jz Fin_de_cadena ; jz (jump if zero), comprueba si zf es positivo                               ; Explicar con dibujo
                     ; zf (Zero Flag) se activa cuando el or da de resultado 0 
    call imprimir_caracter ; Si no se cumple que zf sea positivo, llama a la funcion imprimir_caracter
    jmp imprimir_cadena ; Vuelve a llamarse a si misma hasta que sea 0

; Terminar con la cadena

Fin_de_cadena:

    ret ; Vuelve a la direccion que LLAMÓ a la funcion
;Imprimir caracter

imprimir_caracter: ; Función para imprimir un caracterç

;Imprimir un caracter

    mov ah, 0x0E ; Asignamos a ah el valor 0x0E, que es un codigo de funcion para imprimir caracter, y utiliza la interrupcion de BIOS de abajo 
    int 0x10 ; Interrupcion de BIOS para imprimir caracter

    ret

leer_caracter: ; Función para leer un caracter

; Leer un caracter

    mov ah, 0 ; Asignamos a ah el valor 0, que es la función para leer un caracter
    int 0x16 ; Interrupcion de BIOS para leer caracter
    mov [char], al ; Movemos lo que hay almacenado en el registro al la variable char (El caracter)
    ret

;Variables

mensaje_bienvenida db "DarioAleproyecto", 0 ; Primero nombre de la variable, despues db (Define Bytes) para definir datos de tipo byte, definimos una secuencia de bytes
mensaje_prompt db "DarioAleproyecto", 0 ; Despues la cadena introducida
mensaje_caracter_introducido db "Has presionado la tecla: ", 0 ; Por ultimo el valor 0, que marca el final de la cadena
char db 0x00, 0 ; Definimos char, que será un byte
linea_nueva db 0x0D, 0x0A, 0 ; 0x0D representa en ascii el "Carriage Return" (CR), que mueve el cursor al principio de la linea
                             ; 0x0A representa en ascii el "Line Feed" (LF), que mueve el cursor a la siguiente linea


times 510-($-$$) db 0 ; Repetimos 510 veces el byte 0 para que quede completo el sector de 512bytes
dw 0xAA55 ; Firma de arranque
; Esto hace que el bootloader ocupe los 512 bytes necesarios para que sea booteable, ocupa los 512 bytes en el sector de arranque

;Para ejecutar necesitamos nasm, que es nos lo convierte en un archivo binario, y qemu que es el entorno de virtualizacion que usaremsos
; Comando nasm --- nasm -f bin bootloader.asm -o bootloader.bin
;comando qemu ---- qemu-system-i386 -drive file=bootloader.bin,format=raw
; los paquetes son nasm qemu qemu-system