#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "view.h"
#include "game.h"
#include <windows.h>

using namespace  std;

int main(int argc, char* argv[])
{
    // Unused argc, argv
    (void) argc;
    (void) argv;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Window *window = SDL_CreateWindow("Jumping Jett",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    printf("SDL Window created\n");

    DWORD jettThreadId, obstacleCreatorThreadId, obstacleMoverThreadId, viewUpdaterThreadId;
    HANDLE jettThreadHandle, obstacleCreatorThreadHandle, obstacleMoverThreadHandle, viewUpdaterThreadHandle;

    initGame();
    printf("Game initialized successfully\n");

    createAllViews(renderer);
    printf("Game views created\n");
    // Set background color Black
    SDL_SetRenderDrawColor(renderer, 35, 43, 43, 0xFF);
    SDL_RenderClear(renderer);
    // Draw background image, jet image
    drawBackgroundImage(renderer);
    drawJettPoster(renderer);
    drawAppDescription(renderer);
    drawStartButton(renderer);
    // Update screen
    SDL_RenderPresent(renderer);

    bool quit = false;
    while(!quit)
    {
        SDL_Event e;

        // Wait indefinitely for the next available event
        SDL_WaitEvent(&e);

        // User requests quit
        if(e.type == SDL_QUIT)
        {
            quit = true;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            if (isStartButtonClicked(e))
            {
                printf("Start button has been clicked\n");

                if (isGameRunning())
                {
                    TerminateThread(jettThreadHandle, 0);
                    TerminateThread(obstacleCreatorThreadHandle, 0);
                    TerminateThread(obstacleMoverThreadHandle, 0);
                    TerminateThread(viewUpdaterThreadHandle, 0);

                    stopGame();
                    recreateStartButton(renderer, (char*)"START");
                    drawStartButton(renderer);
                }
                else
                {
                    startGame();

                    // Creating the thread for running the game in the background (generating obstacles, making jet fall etc.)
                    jettThreadHandle = CreateThread(
                            0,
                            0,
                            jettThread,
                            renderer,
                            0,
                            &jettThreadId
                            );

                    obstacleCreatorThreadHandle = CreateThread(
                            0,
                            0,
                            obstacleCreatorThread,
                            renderer,
                            0,
                            &obstacleCreatorThreadId
                            );

                    obstacleMoverThreadHandle = CreateThread(
                            0,
                            0,
                            obstacleMoverThread,
                            renderer,
                            0,
                            &obstacleMoverThreadId
                    );

                    viewUpdaterThreadHandle = CreateThread(
                            0,
                            0,
                            viewUpdaterThread,
                            renderer,
                            0,
                            &viewUpdaterThreadId
                    );

                    recreateStartButton(renderer, (char*)"STOP");
                    drawStartButton(renderer);
                }
                SDL_RenderPresent(renderer);
            }
        }
        else if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_SPACE)
            {
                if (isGameRunning())
                {
                    printf("Space bar pressed\n");
                    Player* player = getPlayer();
                    player->startJump();
                }
            }
        }
    }

    CloseHandle(jettThreadHandle);
    CloseHandle(obstacleCreatorThreadHandle);
    CloseHandle(obstacleMoverThreadHandle);
    CloseHandle(viewUpdaterThreadHandle);

    destroyAllViews();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}