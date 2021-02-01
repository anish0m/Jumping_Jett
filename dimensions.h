#ifndef JJGAME_DIMENSIONS_H
#define JJGAME_DIMENSIONS_H

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

/* Player's body dimensions */
#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 100

/* Obstacle's dimensions */
#define OBSTACLE_WIDTH 30
#define OBSTACLE_HEIGHT 100

/* Gameover dimensions */
#define GO_X ((GAME_VIEW_WIDTH / 2) - (GAP * 1.5))
#define GO_Y ((GAME_VIEW_HEIGHT / 2) - (GAP / 2))
#define GO_WIDTH (GAP * 6)
#define GO_HEIGHT GAP

/* Score dimensions */
#define SCORE_X GAP
#define SCORE_Y SMALL_GAP
#define SCORE_WIDTH START_BUTTON_WIDTH
#define SCORE_HEIGHT START_BUTTON_HEIGHT

#endif //JJGAME_DIMENSIONS_H
