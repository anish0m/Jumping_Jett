#include <SDL.h>
#include <SDL_ttf.h>
#include "jumpingjett-view.h"

/* Background image */
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

/* Jett poster */
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

/* App title and description */
TTF_Font* sans = TTF_OpenFont("Sans.ttf", 24);
SDL_Color White = {255, 255, 255};
SDL_Surface* appTitle = TTF_RenderText_Solid(sans, "Jumping Jett", White);
SDL_Rect appTitleRect = { APP_TITLE_X, APP_TITLE_Y, GAP, GAP };
SDL_Texture* appTitleTexture;

void createAppDescription(SDL_Renderer* renderer) {
    appTitleTexture = SDL_CreateTextureFromSurface(renderer, appTitle);
}

void drawAppDescription(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, appTitleTexture, NULL, &appTitleRect);
}

void destroyAppDescription() {
    SDL_DestroyTexture(appTitleTexture);
    SDL_FreeSurface(jettImg);
}

void createAllViews(SDL_Renderer* renderer) {
    createBackgroundImage(renderer);
    createJettPoster(renderer);
    createAppDescription(renderer);
}

void destroyAllViews() {
    destroyBackgroundImage();
    destroyJettPoster();
    destroyAppDescription();
}