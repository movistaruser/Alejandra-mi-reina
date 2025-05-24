org 0x2000    
      
bits 16              

start:

   
    mov ah, 0x00       
    mov al, 0x03        
    int 0x10           


    mov ah, 0x06        
    mov al, 0          
    mov bh, 0x07        
    mov cx, 0x0000     
    mov dx, 0x184F      
    int 0x10            

   
    mov ah, 0x02        
    mov bh, 0x00        
    mov dh, 0x00       
    mov dl, 0x00        
    int 0x10         

    mov al, 1   

    hlt                 
    ret                    
