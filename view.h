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
void drawInitialScore(SDL_Renderer *renderer);
void drawScoreText(SDL_Renderer *renderer);
void drawScoreValue(SDL_Renderer *renderer);
void drawGameOver(SDL_Renderer *renderer);

/* Checking if the mouse has been clicked inside the button area */
bool isStartButtonClicked(SDL_Event mouseDownEvent);

/* Recreating start button (needed everytime you want to update it's text) */
void recreateStartButton(SDL_Renderer *renderer, char *text);

/* Maintaining scores */
void createInitialScore(SDL_Renderer *renderer);
void calculateScoreValue(int score);
void destroyScoreValue();
void recreateScoreValue(SDL_Renderer *renderer, int score);

/* Game over text */
void createGameOver(SDL_Renderer *renderer);
void destroyGameOver();

/**/
void createAllViews(SDL_Renderer *renderer);
void destroyAllViews();

/* Functions to draw game things */
void drawPlayer(SDL_Renderer *renderer, Player* player);
void drawObstacle(SDL_Renderer *renderer, Obstacle* obstacle);
void drawOrb(SDL_Renderer *renderer, Orb* orb);

#endif //JJGAME_VIEW_H
