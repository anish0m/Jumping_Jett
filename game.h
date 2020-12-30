
#ifndef JJGAME_GAME_H
#define JJGAME_GAME_H

#include "view.h"
#include <windows.h>
#include <vector>
using namespace std;

/* Player's body dimensions */
#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 100

/* Obstacle's dimensions */
#define OBSTACLE_WIDTH 30
#define OBSTACLE_HEIGHT 100

/*****************************************************/
class Obstacle
{
public:
    int positionX;
    bool isAtBottom;
    int colorR, colorG, colorB;

    /*
    This is the "constructor" function. 
    This is only called when the obstacle is created by "Obstacle* obstacle = new Obstacle()""
    */
    Obstacle()
    {
        this->isAtBottom = (bool)(rand() % 2);
        this->positionX = GAME_VIEW_WIDTH + GAME_VIEW_X - OBSTACLE_WIDTH; // it should start at the rightmost corner with a little gap to fit it's width
        this->colorR = rand() % 255;
        this->colorG = rand() % 255;
        this->colorB = rand() % 255;
    }

    void moveLeft()
    {
        this->positionX--;
    }

    bool hasReachedLeft()
    {
        return this->positionX <= GAME_VIEW_X;
    }
};

/***************************************************/
class Player
{
public:
    int percentX;
    int percentY;
    bool isJumping;
    int jumpEnergy;
    bool isDead;

    Player()
    {
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

    void fall()
    {
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

    bool hasCollisionWithObstacle(Obstacle *obstacle)
    {
        // Finding the distance between the center of players body and center of the obstacle's body
        int playerMidX = (this->percentX * GAME_VIEW_WIDTH / 100);
        int obstacleMidX = obstacle->positionX - (OBSTACLE_WIDTH / 2);
        int playerToObstacleDistance = abs(playerMidX - obstacleMidX);

        // The minimum distance between player's and obstacle's body center to indicate a "collision"
        int collisionDistance = (PLAYER_WIDTH + OBSTACLE_WIDTH) / 2;

        // No collision happened
        if (playerToObstacleDistance > collisionDistance)
            return false;

        if (obstacle->isAtBottom)
        {
            // Check if player's leg has touched the obstacle's top surface
            int playerLegY = (this->percentY * GAME_VIEW_HEIGHT / 100) + (PLAYER_HEIGHT / 2);
            if (playerLegY >= GAME_VIEW_HEIGHT - OBSTACLE_HEIGHT)
            {
                printf("Down COLLISSION %d %d\n", playerLegY, GAME_VIEW_HEIGHT - OBSTACLE_HEIGHT);
            }
            return playerLegY >= GAME_VIEW_HEIGHT - OBSTACLE_HEIGHT;
        }
        else
        {
            // Check if player's head has touched the obstacle's bottom surface
            int playerHeadY = (this->percentY * GAME_VIEW_HEIGHT / 100) - (PLAYER_HEIGHT / 2);
            if (playerHeadY <= OBSTACLE_HEIGHT)
            {
                printf("Up COLLISSION %d %d\n", playerHeadY, OBSTACLE_HEIGHT);
            }
            return playerHeadY <= OBSTACLE_HEIGHT;
        }
    }
};

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
