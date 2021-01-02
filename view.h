#ifndef JJGAME_VIEW_H
#define JJGAME_VIEW_H

// Dimensions of the whole app window
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 500
#define GAP 50
#define SMALL_GAP 10

// Dimensions of the game area
#define GAME_VIEW_X GAP
#define GAME_VIEW_Y GAP
#define GAME_VIEW_WIDTH ((int)(SCREEN_WIDTH * 0.6))
#define GAME_VIEW_HEIGHT (SCREEN_HEIGHT - GAP - GAP)

// Dimensions of jett poster
#define JETT_WIDTH 170
#define JETT_HEIGHT 230
#define JETT_X (GAP * 2 + GAME_VIEW_WIDTH)

// Dimensions of "Jumping Jett" text
#define APP_TITLE_X GAME_VIEW_WIDTH + GAP + GAP
#define APP_TITLE_Y GAP + JETT_HEIGHT
#define APP_TITLE_WIDTH 220
#define APP_TITLE_HEIGHT GAP

// Dimensions of "Created by"
#define APP_SUBTITLE_X APP_TITLE_X
#define APP_SUBTITLE_Y APP_TITLE_Y + APP_TITLE_HEIGHT + SMALL_GAP
#define APP_SUBTITLE_WIDTH 90
#define APP_SUBTITLE_HEIGHT 20

// Dimensions of "Mohsina Tabassum Rifa"
#define NAME1_X APP_SUBTITLE_X
#define NAME1_Y APP_SUBTITLE_Y + APP_SUBTITLE_HEIGHT + SMALL_GAP
#define NAME1_WIDTH 230
#define NAME1_HEIGHT APP_SUBTITLE_HEIGHT

// Dimension of Akkus name
#define NAME2_X NAME1_X
#define NAME2_Y NAME1_Y + NAME1_HEIGHT + SMALL_GAP
#define NAME2_WIDTH 150
#define NAME2_HEIGHT APP_SUBTITLE_HEIGHT

// Dimension of 3rd guy's name
#define NAME3_X NAME2_X
#define NAME3_Y NAME2_Y + NAME2_HEIGHT + SMALL_GAP
#define NAME3_WIDTH 150
#define NAME3_HEIGHT APP_SUBTITLE_HEIGHT

// Dimensions of the start button
#define START_BUTTON_X GAP
#define START_BUTTON_Y GAP + GAME_VIEW_HEIGHT + SMALL_GAP
#define START_BUTTON_WIDTH 80 - SMALL_GAP
#define START_BUTTON_HEIGHT GAP - SMALL_GAP - SMALL_GAP

/* Functions to draw things */
void drawBackgroundImage(SDL_Renderer *renderer);
void drawJettPoster(SDL_Renderer *renderer);
void drawAppDescription(SDL_Renderer *renderer);
void drawStartButton(SDL_Renderer *renderer);

/* Checks if the mouse has been clicked inside the button area */
bool isStartButtonClicked(SDL_Event mouseDownEvent);

/* Recreate start button (needed everytime you want to update it's text) */
void recreateStartButton(SDL_Renderer *renderer, char *text);

/**/
void createAllViews(SDL_Renderer *renderer);
void destroyAllViews();

/* Functions to draw game things */
void drawPlayer(SDL_Renderer *renderer, int percentX, int percentY);
void drawObstacle(SDL_Renderer *renderer, bool isAtBottom, int percentX, int r, int g, int b);

#endif //JJGAME_VIEW_H
