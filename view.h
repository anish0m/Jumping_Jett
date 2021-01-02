#ifndef JJGAME_VIEW_H
#define JJGAME_VIEW_H

#include "dimensions.h"

/* Functions to draw things */
void drawBackgroundImage(SDL_Renderer *renderer);
void drawJettPoster(SDL_Renderer *renderer);
void drawAppDescription(SDL_Renderer *renderer);
void drawStartButton(SDL_Renderer *renderer);

/* Checks if the mouse has been clicked inside the button area */
bool isStartButtonClicked(SDL_Event mouseDownEvent);

/* Recreate start button (needed everytime you want to update it's text) */
void recreateStartButton(SDL_Renderer *renderer, char *text);

/**/
void createAllViews(SDL_Renderer *renderer);
void destroyAllViews();

/* Functions to draw game things */
void drawPlayer(SDL_Renderer *renderer, int percentX, int percentY);
void drawObstacle(SDL_Renderer *renderer, bool isAtBottom, int percentX, int r, int g, int b);

#endif //JJGAME_VIEW_H
