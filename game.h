
#ifndef JJGAME_GAME_H
#define JJGAME_GAME_H

#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 100

#include "view.h"
#include <windows.h>

class Player {
public:
    int percentX;
    int percentY;
    bool isJumping;
    bool isDead;

    Player() {
        this->percentX = 20;
        this->percentY = 50;
        this->isJumping = false;
        this->isDead = false;
    }

    bool hasTouchedGround()
    {
        return this->percentY >= 88;
    }

    void fall() {
        this->percentY++;
        if (this->hasTouchedGround())
        {
            this->isDead = true;
        }
    }
};

struct GameState {
    bool hasStarted;
    bool hasFinished;
    bool isPaused;

    int score;

    Player* player;
};

DWORD WINAPI runGameBackgroundProcess(void* _renderer);

void initGame();

void startGame(SDL_Renderer* renderer);

void stopGame();

bool hasGameEnded();

bool isGameRunning();

bool hasGameStarted();

#endif //JJGAME_GAME_H
