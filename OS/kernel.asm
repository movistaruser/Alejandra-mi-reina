org 0x1000

bits 16

start:

call limpiar_pantalla

xor si, si
jmp inicio

inicio:
mov si, Mensaje_shell
call imprimir_cadena

shell:
        
        call leer_comando

        jmp shell
    
%include "libs/variables.inc"
%include "libs/comandos.inc"
%include "libs/funciones.inc"
%include "libs/funciones_globales.inc"
%include "comandos/random.inc"
