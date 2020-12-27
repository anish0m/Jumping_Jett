#include <stdio.h>
#include <SDL.h>
#include "game.h"
#include "view.h"
#include <thread>
#include <chrono>

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

void emitGameOverEvent()
{
    SDL_Event event;
    SDL_memset(&event, 0, sizeof(event));
    event.type = EVENT_JUMPING_JETT_GAME_OVER;
    SDL_PushEvent(&event);
}

void runGameBackgroundProcess(SDL_Renderer* renderer)
{
    printf("Starting game background process\n");
    while (isGameRunning())
    {
        drawBackgroundImage(renderer);
        if (!gameState.player->isJumping)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            gameState.player->fall();
        }
        if (gameState.player->isDead)
        {
            stopGame();
            recreateStartButton(renderer, "START");
            drawStartButton(renderer);
            SDL_RenderPresent(renderer);
            emitGameOverEvent();
            break;
        }
        drawPlayer(renderer, gameState.player->percentX, gameState.player->percentY);
        SDL_RenderPresent(renderer);
    }
    printf("Stopping game background process\n");
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
