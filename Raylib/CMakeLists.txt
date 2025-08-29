cmake_minimum_required(VERSION 3.10)
project(TicTacToe VERSION 1.0.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(RAYLIB_PATH "C:/raylib/raylib"  CACHE PATH "Ruta a la instalacion de Raylib")

include_directories($(RAYLIB_PATH)/src)

add_executable(tictactoe tictactoe.c)

target_link_libraries(tictactoe ${RAYLIB_PATH}/src/raylib.lib)

if(WIN32)
    target_link_libraries(tictactoe winmm gdi32 opengl32)
endif()

set_target_properties(tictactoe PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

message(STATUS "Configuracion completada para TaTeTi con RayLib")
message(STATUS "Usando Raylib desde: ${RAYLIB_PATH}")