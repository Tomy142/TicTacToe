#include "raylib.h"
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define BOARD_SIZE 3
#define CELL_SIZE 150
#define LINES_COLOR (Color){35, 31, 32, 1}
#define WINNING_LINE (Color){255, 215, 0, 1}
#define X_COLOR (Color){229, 68, 109, 1}
#define O_COLOR (Color){73, 220, 177, 1}

typedef enum{
    MENU,
    GAMEPLAY,
    GAMEOVER
}GameState;

typedef struct{
    GameState state;
    int board[BOARD_SIZE][BOARD_SIZE];
    int currentPlayer;
    int winner;
    int mouseHoverX;
    int mouseHoverY;
}Game;

void InitGame(Game *game){
    game->state = MENU;
    game->currentPlayer = 1;
    game->winner = 0;

    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            game->board[i][j] = 0;
        }
    }
}

int CheckWinner(Game *game){
    int board[BOARD_SIZE][BOARD_SIZE];

    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            board[i][j] = game->board[i][j];
        }
    }

    for(int i = 0; i < BOARD_SIZE; i++){
        if(board[i][0] != 0 && board[i][0] == board[i][1] &&  board[i][0] == board[i][2]){
            return board[i][0];
        }

        if(board[0][i] != 0 && board[0][i] == board[1][i] &&  board[0][i] == board[2][i]){
            return board[0][i];
        }
    }

    if(board[0][0] != 0 && board[0][0] == board○[1][1] && board[0][0] == board[2][2]){
        return board[0][0];
    }

    if(board[0][2] != 0 && board[0][2] = board[1][1] && board[0][2] == board[2][0]){
        return board[0][2];
    }

    int isFull= 1;
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            if(board[i][j] == 0){
                isFull = 0;
                break;
            }
        }
        if(!isFull)break;
    }
    if(isFull) return 3;

    return 0;
}

void DrawBoard(Game *game){
    int offsetX = (SCREEN_WIDTH - BOARD_SIZE * CELL_SIZE) / 2;
    int offsetY = (SCREEN_WIDTH - BOARD_SIZE * CELL_SIZE) / 2;

    for(int i = 1; i < BOARD_SIZE; i++){
        DrawLine(offsetX + i * CELL_SIZE, offsetY,
                offsetX + i * CELL_SIZE, offsetY + BOARD_SIZE * CELL_SIZE, LINES_COLOR);
        
        DrawLine(offsetX, offsetY + i * CELL_SIZE,
                offsetX + BOARD_SIZE * CELL_SIZE, offsetY + i * CELL_SIZE, LINES_COLOR);
    }

    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            int posX = offsetX + j * CELL_SIZE + CELL_SIZE / 2;
            int posY = offsetY + j * CELL_SIZE + CELL_SIZE / 2;

            if(game->board[i][j] == 1){
                DrawLine(posX - 40, posY - 40, posX + 40, posY + 40, X_COLOR);
                DrawLine(posX + 40, posY - 40, posX - 40, posY + 40, X_COLOR);
            }else if(game->board[i][j] == 2){
                DrawCircleLines(posX, posY, 40, O_COLOR);
            }
        }
    }

    if(game->state == GAMEPLAY && game->mouseHoverX >= 0 && game->mouseHoverY >= 0){
        int hoverX = offsetX + game->mouseHoverX * CELL_SIZE;
        int hoverY = offsetY + game->mouseHoverY * CELL_SIZE;

        DrawRectangleLines(hoverX, hoverY, CELL_SIZE, CELL_SIZE,
                            (game->currentPlayer  == 1) ? Fade(X_COLOR, 0.5f) : Fade(O_COLOR, 0.5f));
    }
}

void DrawMenu(Game *game){
    DrawText("TaTeTi", SCREEN_WIDTH/2 - MeasureText("TaTeTi", 40)/2, 100, 40, DARKGRAY);
    DrawText("Presiona ESPACIO para comenzar", SCREEN_WIDTH/2 - MesureText("Presiona ESPACIO para comenzar", 20)/2, 200, 20, GRAY);
}