org 0x1000

bits 16

start:

call limpiar_pantalla
mov si, Mensaje_shell
call imprimir_cadena
xor si, si
jmp shell

shell:

        call leer_comando

        jmp shell
    
%include "libs/variables.inc"
%include "libs/variables_shell.inc"
