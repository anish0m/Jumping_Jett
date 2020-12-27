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

void drawAllObstacles(SDL_Renderer* renderer)
{
    for(int i = 0; i < gameState.obstacles.size(); i++)
    {
        Obstacle* obstacle = gameState.obstacles[i];
        drawObstacle(renderer, obstacle->isAtBottom, obstacle->percentX, obstacle->colorR, obstacle->colorG, obstacle->colorB);
    }
}

DWORD WINAPI jettThread(void* _renderer)
{
    SDL_Renderer* renderer = (SDL_Renderer*) _renderer;
    printf("Starting game background process\n");
    while (isGameRunning())
    {
        drawBackgroundImage(renderer);
        if (gameState.player->isJumping)
        {
            Sleep(10);
            gameState.player->rise();
        }
        else
        {
            Sleep(50);
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
        drawAllObstacles(renderer);

        SDL_RenderPresent(renderer);
    }
    printf("Stopping game background process\n");
    return 0;
}

DWORD WINAPI obstacleCreatorThread(void* _renderer)
{
    while(isGameRunning())
    {
        Sleep(2000);
        if (gameState.obstacles.size() < 3)
        {
            printf("Creating obstacle\n");
            generateObstacle();
        }
    }
    return 0;
}

DWORD WINAPI obstacleMoverThread(void* _renderer)
{
    while(isGameRunning())
    {
        Sleep(50);
        vector<int> toRemove;

        for(int i = 0; i < gameState.obstacles.size(); i++)
        {
            Obstacle* obstacle = gameState.obstacles[i];
            obstacle->moveLeft();
            if (obstacle->hasReachedLeft())
            {
                toRemove.push_back(i);
            }
        }

        for (int i = 0; i < toRemove.size(); i++)
        {
            gameState.obstacles.erase(gameState.obstacles.begin() + toRemove[i]);
        }
    }
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

Player* getPlayer()
{
    return gameState.player;
}

void generateObstacle()
{
    Obstacle* obstacle = new Obstacle();
    gameState.obstacles.push_back(obstacle);
}
