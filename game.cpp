#include "game.h"

struct GameState gameState;

void initGame() {
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
    gameState.hasStarted = true;
}

bool hasGameStarted() {
    return gameState.hasStarted;
}
