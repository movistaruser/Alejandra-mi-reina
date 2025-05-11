org 0x1000

bits 16

start:
; %include "libs/intro.inc" 
call limpiar_pantalla
mov si, Mensaje_shell
call imprimir_cadena
jmp shell

shell:

        call leer_caracter
        mov al, [char]

        cmp al, 0x08
        je borrar_caracter

        call imprimir_caracter
        jmp shell
    
%include "libs/variables.inc"
%include "libs/variables_shell.inc"
