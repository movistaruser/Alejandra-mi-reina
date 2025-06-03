


;Variables

mensaje_bienvenida db "DariOS", 0 
char db 0x00, 0 
linea_nueva db 0x0D, 0x0A, 0
mensaje_kernel db "Pulsa cualquier tecla para cargar...", 0
Kernel_check db "Kernel cargado correctamente", 0

cur_fila db 0
cur_columna db 0


Mensaje_shell db "DariOS>", 0
mensaje_error db "Error: no se pudo encontrar el comando ", 0


;variables comandos

cadena_clear db "clear", 0
cadena_hola db "hola", 0
cadena_green db "color green", 0
cadena_color db "color", 0
cadena_blue db "color blue", 0
cadena_red db "color red", 0
cadena_time db "time", 0
cadena_date db "date", 0
cadena_age db "age", 0
cadena_shutdown db "shutdown", 0

; color 
color_error db "Sintaxis incorrecta, prueba a poner algun color", 0

;age
age_int db "Introduce tu edad: ", 0
age_out db "      Tu edad es: "
age_var1 db 0x00, 0
age_var2 db 0x00, 0