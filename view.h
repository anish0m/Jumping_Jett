#ifndef JJGAME_VIEW_H
#define JJGAME_VIEW_H

#define SCREEN_WIDTH    900
#define SCREEN_HEIGHT   500
#define GAP 50
#define SMALL_GAP 10

#define GAME_VIEW_WIDTH (int)(SCREEN_WIDTH * 0.6)
#define GAME_VIEW_HEIGHT SCREEN_HEIGHT - GAP - GAP

#define JETT_WIDTH      170
#define JETT_HEIGHT     230

#define JETT_X      (GAP * 2 + GAME_VIEW_WIDTH)

#define APP_TITLE_X GAME_VIEW_WIDTH + GAP + GAP
#define APP_TITLE_Y GAP + JETT_HEIGHT
#define APP_TITLE_WIDTH 220
#define APP_TITLE_HEIGHT GAP

#define START_BUTTON_X GAP
#define START_BUTTON_Y GAP + GAME_VIEW_HEIGHT + SMALL_GAP
#define START_BUTTON_WIDTH 80
#define START_BUTTON_HEIGHT GAP - SMALL_GAP - SMALL_GAP

void drawBackgroundImage(SDL_Renderer* renderer);

void drawJettPoster(SDL_Renderer* renderer);

void drawAppDescription(SDL_Renderer* renderer);

void drawStartButton(SDL_Renderer* renderer);

void createAllViews(SDL_Renderer* renderer);

void destroyAllViews();

#endif //JJGAME_VIEW_H
