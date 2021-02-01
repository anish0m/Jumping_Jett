#ifndef JJGAME_VIEW_H
#define JJGAME_VIEW_H

#include "dimensions.h"
#include "obstacle.h"
#include "player.h"

/* Functions to draw things */
void drawBackgroundImage(SDL_Renderer *renderer);
void drawJettPoster(SDL_Renderer *renderer);
void drawAppDescription(SDL_Renderer *renderer);
void drawStartButton(SDL_Renderer *renderer);
void drawGameOver(SDL_Renderer *renderer);

/* Checks if the mouse has been clicked inside the button area */
bool isStartButtonClicked(SDL_Event mouseDownEvent);

/* Recreate start button (needed everytime you want to update it's text) */
void recreateStartButton(SDL_Renderer *renderer, char *text);

/**/
void createGameOver(SDL_Renderer *renderer);
void destroyGameOver();

/**/
void createAllViews(SDL_Renderer *renderer);
void destroyAllViews();

/* Functions to draw game things */
void drawPlayer(SDL_Renderer *renderer, Player* player);
void drawObstacle(SDL_Renderer *renderer, Obstacle* obstacle);

#endif //JJGAME_VIEW_H
