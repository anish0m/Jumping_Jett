
#ifndef JJGAME_GAME_H
#define JJGAME_GAME_H

#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 100

class Player {
public:
    int percentX;
    int percentY;

    Player() {
        this->percentX = 20;
        this->percentY = 50;
    }
};

struct GameState {
    bool hasStarted;
    bool hasFinished;
    bool isPaused;

    int score;

    Player* player;
};

void initGame();

void startGame();

void stopGame();

bool hasGameEnded();

bool isGameRunning();

bool hasGameStarted();

char* getStartButtonLabel();

Player* getPlayer();

#endif //JJGAME_GAME_H
