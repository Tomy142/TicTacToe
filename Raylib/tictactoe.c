#include "raylib.h"
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define BOARD_SIZE 3
#define CELL_SIZE 150

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
}