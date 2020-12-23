#include <SDL.h>
#include "jumpingjett-view.h"

SDL_Rect backgroundImageBoundaries = { GAP, GAP, GAME_VIEW_WIDTH, GAME_VIEW_HEIGHT };
SDL_Surface *backgroundImg;
SDL_Texture *backgroundImgTexture;

void createBackgroundImage(SDL_Renderer* renderer) {
    backgroundImg = SDL_LoadBMP("../background.bmp");
    backgroundImgTexture = SDL_CreateTextureFromSurface(renderer, backgroundImg);
}

void drawBackgroundImage(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, backgroundImgTexture, NULL, &backgroundImageBoundaries);
}

void destroyBackgroundImage() {
    SDL_DestroyTexture(backgroundImgTexture);
    SDL_FreeSurface(backgroundImg);
}

SDL_Rect jettImageBoundaries = {JETT_X, GAP, JETT_WIDTH, JETT_HEIGHT };
SDL_Surface *jettImg;
SDL_Texture *jettPosterTexture;

void createJettPoster(SDL_Renderer* renderer) {
    jettImg = SDL_LoadBMP("../Jett.bmp");
    jettPosterTexture = SDL_CreateTextureFromSurface(renderer, jettImg);
}

void drawJettPoster(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, jettPosterTexture, NULL, &jettImageBoundaries);
}

void destroyJettPoster() {
    SDL_DestroyTexture(jettPosterTexture);
    SDL_FreeSurface(jettImg);
}

void createAllViews(SDL_Renderer* renderer) {
    createBackgroundImage(renderer);
    createJettPoster(renderer);
}

void destroyAllViews() {
    destroyBackgroundImage();
    destroyJettPoster();
}