#ifndef JJGAME_ORB_H
#define JJGAME_ORB_H

#endif //JJGAME_ORB_H

#include <bits/stdc++.h>
#include <stdlib.h>
#include "dimensions.h"

using namespace std;

class Orb
{
public :
    int orbX;
    int orbY;

    Orb()
    {
        this->orbX = GAME_VIEW_WIDTH + GAME_VIEW_X - ORB_SIDE;
        this->orbY = 151 + (rand() % 100);
    }

    void moveOrbLeft()
    {
        this->orbX--;
    }

    bool orbReachedLeft()
    {
        return this->orbX <= GAME_VIEW_X;
    }
};