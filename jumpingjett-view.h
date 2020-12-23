#ifndef JJGAME_JUMPINGJETT_VIEW_H
#define JJGAME_JUMPINGJETT_VIEW_H

#define SCREEN_WIDTH    900
#define SCREEN_HEIGHT   500
#define GAP 50

#define GAME_VIEW_WIDTH (int)(SCREEN_WIDTH * 0.6)
#define GAME_VIEW_HEIGHT SCREEN_HEIGHT - GAP - GAP

// RIFA: define Jett poster's dimensions (width 170, height 200) as above
#define JETT_WIDTH      170
#define JETT_HEIGHT     200

#define JETT_X      (GAP * 3 + GAME_VIEW_WIDTH)
#define JETT_Y      (GAP * 4)

void drawBackgroundImage(SDL_Renderer* renderer, SDL_Surface *backgroundImg, SDL_Texture *texture);

// RIFA: create a function prototype "drawJettPoster" like the above
void drawJettPoster(SDL_Renderer* renderer, SDL_Surface *jettImg, SDL_Texture *texture);

#endif //JJGAME_JUMPINGJETT_VIEW_H
