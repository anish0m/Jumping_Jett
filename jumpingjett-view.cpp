#include <SDL.h>
#include "jumpingjett-view.h"

void drawBackgroundImage(SDL_Renderer* renderer, SDL_Surface *backgroundImg, SDL_Texture *texture) {
    SDL_Rect backgroundImageBoundaries = { PADDING, PADDING, (int)(SCREEN_WIDTH * 0.6), SCREEN_HEIGHT - PADDING - PADDING };

    backgroundImg = SDL_LoadBMP("../background.bmp");
    texture = SDL_CreateTextureFromSurface(renderer, backgroundImg);
    SDL_RenderCopy(renderer, texture, NULL, &backgroundImageBoundaries);
}