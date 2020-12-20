#include <SDL.h>
#include "jumpingjett-view.h"

void drawBackgroundImage(SDL_Renderer* renderer, SDL_Surface *backgroundImg, SDL_Texture *texture) {
    SDL_Rect backgroundImageBoundaries = { GAP, GAP, GAME_VIEW_WIDTH, GAME_VIEW_HEIGHT };
    backgroundImg = SDL_LoadBMP("../background.bmp");
    texture = SDL_CreateTextureFromSurface(renderer, backgroundImg);
    SDL_RenderCopy(renderer, texture, NULL, &backgroundImageBoundaries);
}

// RIFA: Implement "drawJettPoster" as same way as above with "Jett.bmp" image file