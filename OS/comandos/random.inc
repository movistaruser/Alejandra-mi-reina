

section .data
seed dd 0x12345678  ; Variable global seed de 32 bits
buffer_numero resb 6
section .text
global _srand
global _rand

_srand:
    push bp
    mov bp, sp
    mov ax, [bp + 4]   ; low word de new_seed
    mov bx, [bp + 6]   ; high word de new_seed
    mov [seed], ax
    mov [seed + 2], bx
    pop bp
    ret

_rand:
    push bp
    mov bp, sp
    push di
    push si

    ; seed = seed * 1103515245 + 12345
    ; 1103515245 = 0x41C64E6D = $41C6:$4E6D

    ; Carga seed
    mov ax, [seed]
    mov dx, [seed + 2]

    ; Multiplicación simple (no completa): ax = ax * 0x4E6D + dx * 0x41C6 << 16
    ; Aquí usamos solo parte baja por simplicidad
    mov bx, 0x4E6D
    mul bx         ; AX = AX * BX (parte baja)
    add ax, 0x3039 ; +12345
    adc dx, 0      ; Ajuste de acarreo

    mov [seed], ax
    mov [seed + 2], dx

    ; return (unsigned short)(seed >> 16)
    mov ax, dx     ; Parte alta del seed

    pop si
    pop di
    pop bp
    ret