org 0x2000           ; Establecer la dirección de inicio

bits 16              ; Asegurar que el código sea en 16 bits

start:

    ; Establecer el modo de vídeo 80x25, texto, color estándar (modo 3)
    mov ah, 0x00        ; Función para establecer el modo de vídeo
    mov al, 0x03        ; Modo 3: 80x25, texto, color
    int 0x10            ; Llamada a la BIOS para configurar el modo

    ; Limpiar la pantalla (scroll up)
    mov ah, 0x06        ; Función de scroll up
    mov al, 0           ; 0 = limpiar toda la pantalla
    mov bh, 0x07        ; Atributo: fondo negro, texto gris claro (07h)
    mov cx, 0x0000      ; Esquina superior izquierda (fila 0, columna 0)
    mov dx, 0x184F      ; Esquina inferior derecha (fila 24, columna 79)
    int 0x10            ; Llamada a la BIOS

    ; Mover el cursor a la fila 0, columna 0 (esquina superior izquierda)
    mov ah, 0x02        ; Función de mover cursor
    mov bh, 0x00        ; Página 0
    mov dh, 0x00        ; Fila 0
    mov dl, 0x00        ; Columna 0
    int 0x10            ; Llamada a la BIOS

    hlt                 ; Detener el sistema
    ret                 ; Retorno, aunque no se ejecutará debido a 'hlt'
