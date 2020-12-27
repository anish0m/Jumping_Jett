
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
    int jumpEnergy;
    bool isDead;

    Player() {
        this->percentX = 20;
        this->percentY = 50;
        this->isJumping = false;
        this->jumpEnergy = 0;
        this->isDead = false;
    }

    bool hasTouchedGround()
    {
        return this->percentY >= 88;
    }

    bool hasTouchedCeiling()
    {
        return this->percentY <= 12;
    }

    void fall() {
        this->percentY++;
        if (this->hasTouchedGround())
        {
            this->isDead = true;
        }
    }

    void startJump()
    {
        this->isJumping = true;
        this->jumpEnergy = 20;
    }

    void rise()
    {
        if (this->isJumping && this->jumpEnergy > 0)
        {
            this->jumpEnergy--;
            this->percentY--;

            if (this->hasTouchedCeiling())
            {
                this->isDead = true;
            }
            if (this->jumpEnergy == 0)
            {
                this->isJumping = false;
            }
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

Player* getPlayer();

#endif //JJGAME_GAME_H
