#include <SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include "view.h"
#include "game.h"

/********************************************************************/
/* Background image */
SDL_Rect backgroundImageBoundaries = { GAP, GAP, GAME_VIEW_WIDTH, GAME_VIEW_HEIGHT };
SDL_Surface *backgroundImg;
SDL_Texture *backgroundImgTexture;

void createBackgroundImage(SDL_Renderer* renderer) {
    printf("Create background image\n");
    backgroundImg = SDL_LoadBMP("../images/background.bmp");
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

/********************************************************************/
/* Jett poster */
SDL_Rect jettImageBoundaries = {JETT_X, GAP, JETT_WIDTH, JETT_HEIGHT };
SDL_Surface *jettImg;
SDL_Texture *jettPosterTexture;

void createJettPoster(SDL_Renderer* renderer) {
    printf("Creating jett poster\n");
    jettImg = SDL_LoadBMP("../images/Jett.bmp");
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

/********************************************************************/
/* App title and description */
SDL_Color white = {255, 255, 255};

SDL_Rect appTitleRect = { APP_TITLE_X, APP_TITLE_Y, APP_TITLE_WIDTH , APP_TITLE_HEIGHT };
SDL_Texture* appTitleTexture;
SDL_Surface* appTitleSurface;

SDL_Rect appSubtitleRect = { APP_SUBTITLE_X, APP_SUBTITLE_Y, APP_SUBTITLE_WIDTH , APP_SUBTITLE_HEIGHT };
SDL_Texture* appSubtitleTexture;
SDL_Surface* appSubtitleSurface;

SDL_Rect name1Rect = { NAME1_X, NAME1_Y, NAME1_WIDTH , NAME1_HEIGHT };
SDL_Texture* name1Texture;
SDL_Surface* name1Surface;

SDL_Rect name2Rect = { NAME2_X, NAME2_Y, NAME2_WIDTH , NAME2_HEIGHT };
SDL_Texture* name2Texture;
SDL_Surface* name2Surface;

SDL_Rect name3Rect = { NAME3_X, NAME3_Y, NAME3_WIDTH , NAME3_HEIGHT };
SDL_Texture* name3Texture;
SDL_Surface* name3Surface;

void createAppDescription(SDL_Renderer* renderer) {
    printf("Loading font and creating app description\n");

    TTF_Font* sans = TTF_OpenFont("../fonts/OpenSans-Regular.ttf", APP_TITLE_HEIGHT * 3);

    appTitleSurface = TTF_RenderText_Solid(sans, "Jumping Jett", white);
    appTitleTexture = SDL_CreateTextureFromSurface(renderer, appTitleSurface);

    sans = TTF_OpenFont("../fonts/OpenSans-Regular.ttf", APP_SUBTITLE_HEIGHT * 3);

    appSubtitleSurface = TTF_RenderText_Solid(sans, "Created by", white);
    appSubtitleTexture = SDL_CreateTextureFromSurface(renderer, appSubtitleSurface);

    name1Surface = TTF_RenderText_Solid(sans, "Mohsina Tabassum Rifa", white);
    name1Texture = SDL_CreateTextureFromSurface(renderer, name1Surface);

    name2Surface = TTF_RenderText_Solid(sans, "Saklain Mahmud", white);
    name2Texture = SDL_CreateTextureFromSurface(renderer, name2Surface);

    name3Surface = TTF_RenderText_Solid(sans, "Zaed Bin Monir", white);
    name3Texture = SDL_CreateTextureFromSurface(renderer, name3Surface);

    TTF_CloseFont(sans);
}

void drawAppDescription(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, appTitleTexture, NULL, &appTitleRect);
    SDL_RenderCopy(renderer, appSubtitleTexture, NULL, &appSubtitleRect);
    SDL_RenderCopy(renderer, name1Texture, NULL, &name1Rect);
    SDL_RenderCopy(renderer, name2Texture, NULL, &name2Rect);
    SDL_RenderCopy(renderer, name3Texture, NULL, &name3Rect);
}

void destroyAppDescription() {
    printf("Destroying app description\n");

    SDL_DestroyTexture(appTitleTexture);
    SDL_FreeSurface(appTitleSurface);

    SDL_DestroyTexture(appSubtitleTexture);
    SDL_FreeSurface(appSubtitleSurface);

    SDL_DestroyTexture(name1Texture);
    SDL_FreeSurface(name1Surface);
}

/********************************************************************/
/* Start Button */
SDL_Color black = {0, 0, 0};
SDL_Rect startButtonRect = { START_BUTTON_X, START_BUTTON_Y, START_BUTTON_WIDTH, START_BUTTON_HEIGHT };
SDL_Rect startButtonTitleRect = { START_BUTTON_X + SMALL_GAP, START_BUTTON_Y + 5, START_BUTTON_WIDTH - SMALL_GAP - 5, START_BUTTON_HEIGHT - SMALL_GAP};
SDL_Texture* startButtonTitleTexture;
SDL_Surface* startButtonTitleSurface;

void createStartButton(SDL_Renderer* renderer, char* text) {
    printf("Creating start button\n");
    TTF_Font* sans = TTF_OpenFont("../fonts/OpenSans-Bold.ttf", 32);
    startButtonTitleSurface = TTF_RenderText_Solid(sans, text, black);
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

void recreateStartButton(SDL_Renderer* renderer, char* text) {
    printf("Recreating the start button\n");
    destroyStartButton();
    createStartButton(renderer, text);
}


/***********************************************/
SDL_Surface *playerImg;
SDL_Texture *playerTexture;

void createPlayerView(SDL_Renderer* renderer)
{
    printf("Creating player view\n");
    playerImg = SDL_LoadBMP("../images/player_default.bmp");
    playerTexture = SDL_CreateTextureFromSurface(renderer, playerImg);
}

void drawPlayer(SDL_Renderer* renderer, int percentX, int percentY)
{
    int playerX = (GAME_VIEW_WIDTH * percentX) / 100;
    playerX -= (PLAYER_WIDTH / 2);

    int playerY = GAME_VIEW_HEIGHT;
    playerY = (playerY * percentY) / 100;
    playerY -= (PLAYER_HEIGHT / 2);

    SDL_Rect playerImageBoundaries = {
            GAME_VIEW_X + playerX,
            GAME_VIEW_Y + playerY,
            PLAYER_WIDTH,
            PLAYER_HEIGHT
    };
    SDL_RenderCopy(renderer, playerTexture, NULL, &playerImageBoundaries);
}

void destroyPlayerView()
{
    printf("Destroying player view\n");
    SDL_DestroyTexture(playerTexture);
    SDL_FreeSurface(playerImg);
}

/***************************************/
void drawObstacle(SDL_Renderer* renderer, bool isAtBottom, int percentX, int r, int g, int b)
{
    int x = GAME_VIEW_X + ((GAME_VIEW_WIDTH * percentX) / 100) - OBSTACLE_WIDTH;
    int y = isAtBottom ? GAME_VIEW_Y + GAME_VIEW_HEIGHT - OBSTACLE_HEIGHT: GAME_VIEW_Y;

    SDL_Rect obstacleRect = { x, y, OBSTACLE_WIDTH, OBSTACLE_HEIGHT };
    SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
    SDL_RenderFillRect(renderer, &obstacleRect);
}

/********************************************************************/
void createAllViews(SDL_Renderer* renderer) {
    createBackgroundImage(renderer);
    createJettPoster(renderer);
    createAppDescription(renderer);
    createStartButton(renderer, "START");
    createPlayerView(renderer);
}

void destroyAllViews() {
    destroyBackgroundImage();
    destroyJettPoster();
    destroyAppDescription();
    destroyStartButton();
    destroyPlayerView();
}
