start:

call limpiar_pantalla
jmp blanco_negro

blanco_negro:
call limpiar_pantalla
mov bh, 0x0700      ; atributo: fondo negro, texto gris claro (07h)
mov al, "A"
call imprimir_caracter
call delay
jmp negro_negro

negro_negro:
call limpiar_pantalla
mov bh, 0x0700      ; atributo: fondo negro, texto gris claro (07h)
mov al, "B"
call imprimir_caracter
call delay
jmp blanco_negro


