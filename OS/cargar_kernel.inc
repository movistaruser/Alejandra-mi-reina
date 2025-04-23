mov ax,Dir_Kernel
	mov ds,ax
	mov ss,ax
	mov es,ax
    mov ax,0xfff0
	mov sp,ax
	mov bp,ax

    mov     cl,Sector_Inicio+1      ;cl holds sector number
    mov     dh,0     ;dh holds head number - 0
    mov     ch,0     ;ch holds track number - 0
    mov     ah,2            ;absolute disk read
    mov     al,Sectores_Max        ;read KSIZE sectors
    mov     dl,0            ;read from floppy disk A
    mov     bx,0		;read into 0 (in the segment)
    int     13h	;call BIOS disk read function

    Kernel_check db "Kernel cargado correctamente", 0