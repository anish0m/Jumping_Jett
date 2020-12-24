#include <stdio.h>
#include "game.h"

struct GameState gameState;

void initGame() {
    printf("Resetting Game State\n");
    gameState = {
            false,
            false,
            false,
            0,
            25,
            50,
    };
}

void startGame() {
    printf("Starting the game\n");
    gameState.hasStarted = true;
    gameState.hasFinished = false;
}

void stopGame() {
    printf("Stopping the game\n");
    gameState.hasStarted = true;
    gameState.hasFinished = true;
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
