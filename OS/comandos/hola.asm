org 0x3000

bits 16

start:
     

    mov si, hola_mundo
    call imprimir_cadena


    retf
    
    

    hola_mundo db "Hola mundo", 0
    %include "libs/variables.inc"