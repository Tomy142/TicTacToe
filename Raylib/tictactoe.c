#include "raylib.h"
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define BOARD_SIZE 3
#define CELL_SIZE 150
#define BACKGROUND_COLOR (Color){240, 240, 240, 255}
#define GRID_LINE_WIDTH  5.0f 
#define LINES_COLOR (Color){35, 31, 32, 255}
#define BOARD_COLOR (Color){110, 110, 110, 1}
#define WINNING_LINE (Color){255, 215, 0, 255}
#define X_COLOR (Color){229, 68, 109, 255}
#define O_COLOR (Color){73, 220, 177, 255}

typedef enum{
    MENU,
    GAMEPLAY,
    GAME_OVER
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

    if(board[0][0] != 0 && board[0][0] == board[1][1] && board[0][0] == board[2][2]){
        return board[0][0];
    }

    if(board[0][2] != 0 && board[0][2] == board[1][1] && board[0][2] == board[2][0]){
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
    int offsetY = (SCREEN_HEIGHT - BOARD_SIZE * CELL_SIZE) / 2;

    DrawRectangle(offsetX - 15, offsetY -15,
                    BOARD_SIZE * CELL_SIZE + 30,
                    BOARD_SIZE * CELL_SIZE +30,
                    WHITE);

    for(int i = 1; i < BOARD_SIZE; i++){
        DrawLineEx((Vector2){offsetX + i * CELL_SIZE, offsetY},
                (Vector2){offsetX + i * CELL_SIZE, offsetY + BOARD_SIZE * CELL_SIZE}, 5.0f, LINES_COLOR);
        
        DrawLineEx((Vector2){offsetX, offsetY + i * CELL_SIZE},
                (Vector2){offsetX + BOARD_SIZE * CELL_SIZE, offsetY + i * CELL_SIZE}, 5.0f, LINES_COLOR);
    }

    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            int posX = offsetX + j * CELL_SIZE + CELL_SIZE / 2;
            int posY = offsetY + i * CELL_SIZE + CELL_SIZE / 2;

            if(game->board[i][j] == 1){
                DrawLineEx((Vector2){posX - 40, posY - 40},(Vector2){ posX + 40, posY + 40}, 8.0f, X_COLOR);
                DrawLineEx((Vector2){posX + 40, posY - 40},(Vector2){ posX - 40, posY + 40}, 8.0f, X_COLOR);
            }else if(game->board[i][j] == 2){
                DrawRing((Vector2){posX, posY},30, 35,0, 360, 0, O_COLOR);
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
    DrawText("Presiona ESPACIO para comenzar", SCREEN_WIDTH/2 - MeasureText("Presiona ESPACIO para comenzar", 20)/2, 200, 20, GRAY);
}

void DrawGameOver(Game* game){
    DrawBoard(game);

    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(RAYWHITE, 0.8f));

    if(game->winner == 3){
        DrawText("¡Empate!", SCREEN_WIDTH/2 - MeasureText("¡Empate!", 40)/2, 100, 40,DARKGRAY);
    } else{
        const char *winnerText = (game->winner == 1) ? "!X Gana!" : "¡O Gana!";
        DrawText(winnerText, SCREEN_WIDTH/2 - MeasureText(winnerText, 40)/2, 100, 40, (game->winner == 1) ? X_COLOR : O_COLOR);
    }

    DrawText("Presiona R para reiniciar", SCREEN_WIDTH/2 - MeasureText("Presiona R para reiniciar", 20)/2, 200, 20, GRAY);
}

int main(void){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TaTeTi con Raylib");
    SetTargetFPS(60);

    Game game;
    InitGame(&game);

    while(!WindowShouldClose()){
        if(game.state == MENU){
            if(IsKeyPressed(KEY_SPACE)){
                game.state = GAMEPLAY;
            }
        }else if(game.state == GAMEPLAY){
            int offsetX = (SCREEN_WIDTH - BOARD_SIZE * CELL_SIZE) /2;
            int offsetY = (SCREEN_HEIGHT - BOARD_SIZE * CELL_SIZE) /2;

            Vector2 mousePos = GetMousePosition();
            game.mouseHoverX = -1;
            game.mouseHoverY = -1;

            if(mousePos.x >= offsetX && mousePos.x <= offsetX + BOARD_SIZE * CELL_SIZE && 
                mousePos.y >= offsetY && mousePos.y <= offsetY + BOARD_SIZE * CELL_SIZE){
                    game.mouseHoverX = (int)((mousePos.x - offsetX) / CELL_SIZE);
                    game.mouseHoverY = (int)((mousePos.y - offsetY) / CELL_SIZE);

                    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        if(game.board[game.mouseHoverY][game.mouseHoverX]== 0){
                            game.board[game.mouseHoverY][game.mouseHoverX] = game.currentPlayer;

                            game.winner = CheckWinner(&game);
                            if(game.winner != 0){
                                game.state = GAME_OVER;
                            }else{
                                game.currentPlayer = (game.currentPlayer == 1) ? 2 : 1;
                            }
                        }
                    }
                }
        }else if(game.state == GAME_OVER){
            if(IsKeyPressed(KEY_R)){
                InitGame(&game);
            }
        }
        BeginDrawing();
        ClearBackground(LINES_COLOR);

        if(game.state == MENU){
            DrawMenu(&game);
        }else if(game.state == GAMEPLAY){
            DrawText("TaTeTi", SCREEN_WIDTH/2 - MeasureText("TaTeTi", 30)/2, 30, 30, DARKGRAY);

            const char *turnText = (game.currentPlayer == 1) ? "Turno: X" : "Turno: O";
            Color turnColor = (game.currentPlayer == 1) ? X_COLOR : O_COLOR;
            DrawText(turnText, SCREEN_WIDTH/2 - MeasureText(turnText, 20)/2, 70, 20, turnColor);

            DrawBoard(&game);
        }else if(game.state == GAME_OVER){
            DrawGameOver(&game);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}