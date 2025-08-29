#!/bin/bash

# Colores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "==============================="
echo "   TICTACTOE - COMPILADOR"
echo "==============================="

# Verificar si GCC está instalado
if ! command -v gcc &> /dev/null; then
    echo -e "${RED}ERROR: GCC no está instalado${NC}"
    echo "Instala GCC con: sudo apt install build-essential"
    exit 1
fi

# Verificar estructura de archivos
if [ ! -f "tictactoe.c" ]; then
    echo -e "${RED}ERROR: No se encuentra tictactoe.c${NC}"
    exit 1
fi

if [ ! -f "libs/raylib/include/raylib.h" ]; then
    echo -e "${RED}ERROR: raylib.h no encontrado${NC}"
    echo "Busca en: libs/raylib/include/raylib.h"
    exit 1
fi

if [ ! -f "libs/raylib/lib/libraylib.a" ]; then
    echo -e "${RED}ERROR: libraylib.a no encontrado${NC}"
    echo "Busca en: libs/raylib/lib/libraylib.a"
    exit 1
fi

echo -e "${GREEN}Estructura verificada: ✅${NC}"
echo "  - libs/raylib/include/raylib.h"
echo "  - libs/raylib/lib/libraylib.a"
echo ""

echo "Compilando..."
gcc -o tictactoe tictactoe.c \
    -I "libs/raylib/include" \
    -L "libs/raylib/lib" \
    -lraylib -lm -lpthread -ldl \
    -Wall -std=c99

if [ $? -eq 0 ]; then
    echo ""
    echo -e "${GREEN}¡COMPILACIÓN EXITOSA! ✅${NC}"
    echo "==============================="
    echo "Ejecutando el juego..."
    echo "==============================="
    sleep 2
    ./tictactoe
else
    echo ""
    echo -e "${RED}ERROR en la compilación ❌${NC}"
    echo "Revisa el código fuente"
    exit 1
fi