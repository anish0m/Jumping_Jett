#include <SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include "view.h"
#include "game.h"

/* Background image */
SDL_Rect backgroundImageBoundaries = { GAP, GAP, GAME_VIEW_WIDTH, GAME_VIEW_HEIGHT };
SDL_Surface *backgroundImg;
SDL_Texture *backgroundImgTexture;

void createBackgroundImage(SDL_Renderer* renderer) {
    printf("Create background image\n");
    backgroundImg = SDL_LoadBMP("../background.bmp");
    backgroundImgTexture = SDL_CreateTextureFromSurface(renderer, backgroundImg);
}

void drawBackgroundImage(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, backgroundImgTexture, NULL, &backgroundImageBoundaries);
}

void destroyBackgroundImage() {
    printf("Destroying background image\n");
    SDL_DestroyTexture(backgroundImgTexture);
    SDL_FreeSurface(backgroundImg);
}

/* Jett poster */
SDL_Rect jettImageBoundaries = {JETT_X, GAP, JETT_WIDTH, JETT_HEIGHT };
SDL_Surface *jettImg;
SDL_Texture *jettPosterTexture;

void createJettPoster(SDL_Renderer* renderer) {
    printf("Creating jett poster\n");
    jettImg = SDL_LoadBMP("../Jett.bmp");
    jettPosterTexture = SDL_CreateTextureFromSurface(renderer, jettImg);
}

void drawJettPoster(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, jettPosterTexture, NULL, &jettImageBoundaries);
}

void destroyJettPoster() {
    printf("Destroying jett poster\n");
    SDL_DestroyTexture(jettPosterTexture);
    SDL_FreeSurface(jettImg);
}

/* App title and description */
SDL_Color white = {255, 255, 255};
SDL_Rect appTitleRect = { APP_TITLE_X, APP_TITLE_Y, APP_TITLE_WIDTH , APP_TITLE_HEIGHT };
SDL_Texture* appTitleTexture;
SDL_Surface* appTitleSurface;

void createAppDescription(SDL_Renderer* renderer) {
    printf("Loading font and creating app description\n");
    TTF_Font* sans = TTF_OpenFont("../OpenSans-Regular.ttf", 24);
    appTitleSurface = TTF_RenderText_Solid(sans, "Jumping Jett", white);
    appTitleTexture = SDL_CreateTextureFromSurface(renderer, appTitleSurface);
    TTF_CloseFont(sans);
}

void drawAppDescription(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, appTitleTexture, NULL, &appTitleRect);
}

void destroyAppDescription() {
    printf("Destroying app description\n");
    SDL_DestroyTexture(appTitleTexture);
    SDL_FreeSurface(appTitleSurface);
}

/* Start Button */
SDL_Color black = {0, 0, 0};
SDL_Rect startButtonRect = { START_BUTTON_X, START_BUTTON_Y, START_BUTTON_WIDTH, START_BUTTON_HEIGHT };
SDL_Rect startButtonTitleRect = { START_BUTTON_X + SMALL_GAP, START_BUTTON_Y + 5, START_BUTTON_WIDTH - SMALL_GAP - 5, START_BUTTON_HEIGHT - SMALL_GAP};
SDL_Texture* startButtonTitleTexture;
SDL_Surface* startButtonTitleSurface;

void createStartButton(SDL_Renderer* renderer) {
    printf("Creating start button\n");
    TTF_Font* sans = TTF_OpenFont("../OpenSans-Bold.ttf", 16);
    startButtonTitleSurface = TTF_RenderText_Solid(sans, getStartButtonLabel(), black);
    startButtonTitleTexture = SDL_CreateTextureFromSurface(renderer, startButtonTitleSurface);
    TTF_CloseFont(sans);
}

void drawStartButton(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(renderer, &startButtonRect);
    SDL_RenderCopy(renderer, startButtonTitleTexture, NULL, &startButtonTitleRect);
}

void destroyStartButton() {
    printf("Destroying start button\n");
    SDL_DestroyTexture(startButtonTitleTexture);
    SDL_FreeSurface(startButtonTitleSurface);
}

bool isStartButtonClicked(SDL_Event mouseDownEvent) {
    auto x = mouseDownEvent.button.x;
    auto y = mouseDownEvent.button.y;

    return x >= START_BUTTON_X && x <= (START_BUTTON_X + START_BUTTON_WIDTH)
        && y >= START_BUTTON_Y && y <= (START_BUTTON_Y + START_BUTTON_HEIGHT);
}

void redrawStartButton(SDL_Renderer* renderer) {
    printf("Recreating the start button\n");
    destroyStartButton();
    createStartButton(renderer);
}

void createAllViews(SDL_Renderer* renderer) {
    createBackgroundImage(renderer);
    createJettPoster(renderer);
    createAppDescription(renderer);
    createStartButton(renderer);
}

void destroyAllViews() {
    destroyBackgroundImage();
    destroyJettPoster();
    destroyAppDescription();
    destroyStartButton();
}