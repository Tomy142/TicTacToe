@echo off
chcp 65001 > nul
title Compilador TaTeTi Portable

echo ===============================
echo    TICTACTOE - COMPILADOR
echo ===============================

echo Estructura verificada: ✅
echo   - libs/raylib/include/raylib.h
echo   - libs/raylib/lib/libraylib.a
echo.

echo Compilando...
gcc -o tictactoe.exe tictactoe.c ^
    -I "libs/raylib/include" ^
    -L "libs/raylib/lib" ^
    -lraylib -lgdi32 -lwinmm -lopengl32 ^
    -Wall -std=c99

if %errorlevel% equ 0 (
    echo.
    echo ¡COMPILACIÓN EXITOSA! ✅
    echo ===============================
    echo Ejecutando el juego...
    echo ===============================
    timeout /t 2 /nobreak >nul
    tictactoe.exe
) else (
    echo.
    echo ERROR en la compilación ❌
    echo Revisa el código fuente
)

pause