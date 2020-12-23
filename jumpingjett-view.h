#ifndef JJGAME_JUMPINGJETT_VIEW_H
#define JJGAME_JUMPINGJETT_VIEW_H

#define SCREEN_WIDTH    900
#define SCREEN_HEIGHT   500
#define GAP 50

#define GAME_VIEW_WIDTH (int)(SCREEN_WIDTH * 0.6)
#define GAME_VIEW_HEIGHT SCREEN_HEIGHT - GAP - GAP

#define JETT_WIDTH      170
#define JETT_HEIGHT     230

#define JETT_X      (GAP * 2 + GAME_VIEW_WIDTH)

void drawBackgroundImage(SDL_Renderer* renderer, SDL_Surface *backgroundImg, SDL_Texture *texture);

void drawJettPoster(SDL_Renderer* renderer, SDL_Surface *jettImg, SDL_Texture *texture);

#endif //JJGAME_JUMPINGJETT_VIEW_H
