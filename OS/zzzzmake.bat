nasm -f bin bootloader.asm -o bootloader.bin
nasm -f bin kernel.asm -o kernel.bin
copy /b bootloader.bin + kernel.bin so.img