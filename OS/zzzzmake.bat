nasm -f bin bootloader.asm -o bootloader.bin
nasm -f bin kernel.asm -o kernel.bin
nasm -f bin ./comandos/clear.asm -o clear.bin
nasm -f bin ./comandos/hola.asm -o hola.bin
copy /b bootloader.bin + kernel.bin + clear.bin + hola.bin so.img