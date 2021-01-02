
#ifndef JJGAME_GAME_H
#define JJGAME_GAME_H

#include "view.h"
#include <windows.h>
#include <vector>
#include "dimensions.h"
#include "obstacle.h"
#include "player.h"
using namespace std;

/*
To represent a "moment" in the game, we need to create a game state with some variables that clearly
represent the game. As the time passes, we will modify these variables and take decisions based on them.
*/
struct GameState
{
    bool hasStarted;
    bool hasFinished;
    bool isPaused;

    int score;

    Player *player;
    vector<Obstacle *> obstacles;
};

/* Functions that run only inside a thread */
DWORD WINAPI jettThread(void *_renderer);
DWORD WINAPI obstacleCreatorThread(void *_renderer);
DWORD WINAPI obstacleMoverThread(void *_renderer);
DWORD WINAPI viewUpdaterThread(void *_renderer);

void initGame();
void startGame();
void stopGame();

bool hasGameEnded();
bool isGameRunning();
bool hasGameStarted();

/* Get the pointer to the jett player */
Player *getPlayer();

void generateObstacle();

#endif //JJGAME_GAME_H
