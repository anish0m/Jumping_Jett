#include <SDL.h>
#include "jumpingjett-view.h"

void drawBackgroundImage(SDL_Renderer* renderer, SDL_Surface *backgroundImg, SDL_Texture *texture) {
    SDL_Rect backgroundImageBoundaries = { GAP, GAP, GAME_VIEW_WIDTH, GAME_VIEW_HEIGHT };
    backgroundImg = SDL_LoadBMP("../background.bmp");
    texture = SDL_CreateTextureFromSurface(renderer, backgroundImg);
    SDL_RenderCopy(renderer, texture, NULL, &backgroundImageBoundaries);
}

// RIFA: Implement "drawJettPoster" as same way as above with "Jett.bmp" image file
void drawJettPoster(SDL_Renderer* renderer, SDL_Surface *jettImg, SDL_Texture *texture) {
    SDL_Rect jettImageBoundaries = {JETT_X, JETT_Y, JETT_WIDTH, JETT_HEIGHT };
    jettImg = SDL_LoadBMP("../Jett.bmp");
    texture = SDL_CreateTextureFromSurface(renderer, jettImg);
    SDL_RenderCopy(renderer, texture, NULL, &jettImageBoundaries);
}