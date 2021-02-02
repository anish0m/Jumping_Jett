#ifndef JJGAME_PLAYER_H
#define JJGAME_PLAYER_H

#include "dimensions.h"
#include "obstacle.h"

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
        int tolerance = 5;
        int playerX = (this->percentX * GAME_VIEW_WIDTH / 100) + GAME_VIEW_X - (PLAYER_WIDTH/2);

        if (obstacle->positionX + OBSTACLE_WIDTH - tolerance < playerX)
        {
            return false;
        }

        if (playerX + PLAYER_WIDTH - tolerance < obstacle->positionX)
        {
            return false;
        }

        if (obstacle->isAtBottom)
        {
            // Checking if player's leg has touched the obstacle's top surface
            int playerLegY = (this->percentY * GAME_VIEW_HEIGHT / 100) + (PLAYER_HEIGHT / 2);
            return playerLegY - tolerance > GAME_VIEW_HEIGHT - OBSTACLE_HEIGHT;
        }
        else
        {
            // Checking if player's head has touched the obstacle's bottom surface
            int playerHeadY = (this->percentY * GAME_VIEW_HEIGHT / 100) - (PLAYER_HEIGHT / 2);
            return playerHeadY + tolerance < OBSTACLE_HEIGHT;
        }
    }
};

#endif //JJGAME_PLAYER_H
