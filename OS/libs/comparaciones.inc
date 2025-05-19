comparar_clear:

    mov al, [buffer_shell]    


    mov bl, [cadena_clear]


    cmp bl, 0
    je clear   

    cmp al, bl
    jne ret 

    inc buffer_shell   
    inc cadena_clear  
    jmp comparar_clear


cadena_clear db "clear", 0