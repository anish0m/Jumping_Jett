#include <stdio.h>
#include <SDL.h>
#include "game.h"
#include <windows.h>

struct GameState gameState;

void initGame() {
    printf("Resetting Game State\n");
    gameState = {
            false,
            false,
            false,
            0,
            NULL
    };
}

DWORD WINAPI runGameBackgroundProcess(void* _renderer)
{
    SDL_Renderer* renderer = (SDL_Renderer*) _renderer;
    printf("Starting game background process\n");
    while (isGameRunning())
    {
        drawBackgroundImage(renderer);
        if (!gameState.player->isJumping)
        {
            Sleep(100);
            gameState.player->fall();
        }
        if (gameState.player->isDead)
        {
            stopGame();
            recreateStartButton(renderer, (char*)"START");
            drawStartButton(renderer);
            SDL_RenderPresent(renderer);
            break;
        }
        drawPlayer(renderer, gameState.player->percentX, gameState.player->percentY);
        SDL_RenderPresent(renderer);
    }
    printf("Stopping game background process\n");
    return 0;
}

void startGame(SDL_Renderer* renderer) {
    printf("Starting the game\n");
    gameState.hasStarted = true;
    gameState.hasFinished = false;
    gameState.player = new Player();
}

void stopGame() {
    printf("Stopping the game\n");
    gameState.hasStarted = true;
    gameState.hasFinished = true;
    delete gameState.player;
}

bool hasGameStarted() {
    return gameState.hasStarted;
}

bool hasGameEnded() {
    return gameState.hasFinished;
}

bool isGameRunning() {
    return hasGameStarted() && !hasGameEnded();
}

char* getStartButtonLabel() {
    return isGameRunning() ? (char*)"STOP": (char*)"START";
}
