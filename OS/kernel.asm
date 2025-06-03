org 0x1000

bits 16

start:

call limpiar_buffer

call limpiar_pantalla
mov si, Mensaje_shell
call imprimir_cadena
xor si, si
jmp shell

shell:

        call limpiar_buffer
        call leer_comando
        call limpiar_buffer
        jmp shell
    
%include "libs/variables.inc"
%include "libs/funciones.inc"
%include "libs/comandos.inc"
%include "libs/funciones_globales.inc"

