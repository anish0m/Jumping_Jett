#ifndef JJGAME_OBSTACLE_H
#define JJGAME_OBSTACLE_H

#include <bits/stdc++.h>
#include <stdlib.h>
#include "dimensions.h"

class Obstacle
{
public:
    int positionX;
    bool isAtBottom;
    int colorR, colorG, colorB;

    /*
    This is the "constructor" function.
    We're gonna call it only when the obstacle is created by "Obstacle* obstacle = new Obstacle()""
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

#endif //JJGAME_OBSTACLE_H
