#include <bits/stdc++.h>
#include <windows.h>
#include <SDL.h>
#include "game.h"
#include "variable.h"

struct GameState gameState;

void initGame()
{
    printf("Resetting Game State\n");

    gameState = {
        false,
        false,
        0,
        NULL};
}

void drawAllObstacles(SDL_Renderer *renderer)
{
    for (int i = 0; i < gameState.obstacles.size(); i++)
    {
        Obstacle *obstacle = gameState.obstacles[i];
        drawObstacle(renderer, obstacle);
    }
}

void drawAllOrbs(SDL_Renderer *renderer)
{
    for (int i = 0; i < gameState.orbs.size(); i++)
    {
        Orb *orb = gameState.orbs[i];
        drawOrb(renderer, orb);
    }
}

DWORD WINAPI jettThread(void *_renderer)
{
    Player *player = getPlayer();

    while (isGameRunning())
    {
        if (player->isJumping)
        {
            // If jett is in the JUMP mode, make her go up by 1% in the Y axis every 10 milliseconds
            Sleep(10);
            player->rise();
        }
        else
        {
            // Otherwise, make jett fall by 1% in the Y axis every 50 milliseconds
            Sleep(50);
            player->fall();
        }

        if (player->isDead)
        {
            break;
        }

        // Check if jett has collided with any obstacle
        if (gameState.obstacles.size() > 0)
        {
            Obstacle *obstacle = gameState.obstacles[0];
            if (player->hasCollisionWithObstacle(obstacle))
            {
                player->isDead = true;
                break;
            }
        }

        // Check if jett has collided with any orb
        if (gameState.orbs.size() > 0)
        {
            Orb *orb = gameState.orbs[0];

            if (player->hasCollisionWithOrb(orb))
            {
                effectOfOrb();
            }
        }
    }
    return 0;
}

DWORD WINAPI obstacleCreatorThread(void *_renderer)
{
    while (isGameRunning())
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

DWORD WINAPI obstacleMoverThread(void *_renderer)
{
    SDL_Renderer *renderer = (SDL_Renderer *)_renderer;

    while (isGameRunning())
    {
        Sleep(10);

        vector<int> toRemove;

        if (gameState.player->isDead)
        {
            break;
        }

        // Move all the obstacles left by 1 pixel
        for (int i = 0; i < gameState.obstacles.size(); i++)
        {
            Obstacle *obstacle = gameState.obstacles[i];
            obstacle->moveLeft();

            if (obstacle->hasReachedLeft())
            {
                toRemove.push_back(i);
            }
        }

        // Remove the obstacles that has reached the leftmost corner
        for (int i = 0; i < toRemove.size(); i++)
        {
            gameState.obstacles.erase(gameState.obstacles.begin() + toRemove[i]);

            //Calculating score and updating them
            gameState.score += 10;

            recreateScoreValue(renderer, gameState.score);
            drawScoreValue(renderer);
        }
    }
    return 0;
}

DWORD WINAPI orbCreatorThread(void *_renderer)
{
    while (isGameRunning())
    {
        Sleep(3000);

        if (gameState.orb.size() < 2)
        {
            printf("Creating orb\n");
            generateOrb();
        }
    }
    return 0;
}

DWORD WINAPI orbMoverThread(void *_renderer)
{
    SDL_Renderer *renderer = (SDL_Renderer *)_renderer;

    while (isGameRunning())
    {
        Sleep(10);

        vector<int> orbRemove;

        if (gameState.player->isDead)
        {
            break;
        }

        // Move all the orbs left by 1 pixel
        for (int i = 0; i < gameState.orb.size(); i++)
        {
            Orb *orb = gameState.orbs[i];
            orb->moveOrbLeft();

            if (orb->orbReachedLeft())
            {
                orbRemove.push_back(i);
            }
        }

        // Remove the orbs that has reached the leftmost corner
        for (int i = 0; i < orbRemove.size(); i++)
        {
            gameState.orbs.erase(gameState.orbs.begin() + orbRemove[i]);
        }
    }
    return 0;
}

DWORD WINAPI viewUpdaterThread(void *_renderer)
{
    SDL_Renderer *renderer = (SDL_Renderer *)_renderer;

    while (isGameRunning())
    {
        Sleep(10);

        // Drawing the background image every moment before drawing jett or any obstacle
        drawBackgroundImage(renderer);

        // Drawing Jett at (x%, y%)
        drawPlayer(renderer, gameState.player);

        // Drawing obstacles
        drawAllObstacles(renderer);

        // Refreshing the game screen
        SDL_RenderPresent(renderer);

        if (gameState.player->isDead)
        {
            recreateStartButton(renderer, (char *)"START");
            drawStartButton(renderer);

            drawBackgroundImage(renderer);
            drawAllObstacles(renderer);
            drawPlayer(renderer, gameState.player);

            createGameOver(renderer);
            drawGameOver(renderer);

            SDL_RenderPresent(renderer);

            stopGame();
            break;
        }
    }
    return 0;
}

void startGame()
{
    destroyGameOver();

    printf("Starting the game\n");

    gameState.hasStarted = true;
    gameState.hasFinished = false;
    gameState.player = new Player();
}

void stopGame()
{
    printf("Stopping the game\n");

    gameState.hasStarted = true;
    gameState.hasFinished = true;
    delete gameState.player;
    gameState.obstacles.erase(gameState.obstacles.begin(), gameState.obstacles.end());
}

bool hasGameStarted()
{
    return gameState.hasStarted;
}

bool hasGameEnded()
{
    return gameState.hasFinished;
}

bool isGameRunning()
{
    return hasGameStarted() && !hasGameEnded();
}

Player *getPlayer()
{
    return gameState.player;
}

void generateObstacle()
{
    Obstacle *obstacle = new Obstacle();
    gameState.obstacles.push_back(obstacle);
}

void generateOrb()
{
    Orb *orb = new Orb();
    gameState.orbs.push_back(orb);
}

void effectOfOrb()
{
    if (choose >= 5)
    {
        choose -= 5;
    }

    Player *player = getPlayer();
    SDL_Renderer *renderer;

    if (choose == 0)
    {
        //increase speed of obstacle for 10 sec
    }
    else if (choose == 1)
    {
        //decrease speed of obstacle for 10 sec
    }
    else if (choose == 2)
    {
        //give jett a gun
        //click on an obstacle
        //remove that obstacle
    }
    else if (choose == 3)
    {
        gameState.score += 100;

        recreateScoreValue(renderer, gameState.score);
        drawScoreValue(renderer);
    }
    else
    {
        player->isDead = true;
        break;
    }
}
