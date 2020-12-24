
#ifndef JJGAME_GAME_H
#define JJGAME_GAME_H

#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 100

struct GameState {
    bool hasStarted;
    bool hasFinished;
    bool isPaused;

    int score;

    int jettX;
    int jettY;
};

void initGame();

void startGame();

void stopGame();

bool hasGameEnded();

bool isGameRunning();

bool hasGameStarted();

char* getStartButtonLabel();

#endif //JJGAME_GAME_H
