@echo off
setlocal

rem === Paso 2: Ensamblar bootloader ===
nasm -f bin bootloader.asm -o bootloader.bin
if errorlevel 1 goto error

rem === Paso 3: Ensamblar kernel (que incluye incbin "random.com") ===
nasm -f bin kernel.asm -o kernel.bin
if errorlevel 1 goto error

rem === Paso 4: Crear imagen final concatenando bootloader y kernel ===
copy /b bootloader.bin+kernel.bin so.img
if errorlevel 1 goto error

echo ===============================
echo ✅ Imagen so.img generada correctamente.
echo ===============================
pause
exit /b

:error
echo ❌ Error durante la compilación
pause
exit /b
