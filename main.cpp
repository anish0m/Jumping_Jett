#include <bits/stdc++.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "dimensions.h"
#include "view.h"
#include "game.h"

using namespace std;

int main(int argc, char *argv[])
{
    // Unused argc, argv
    (void)argc;
    (void)argv;

    // Initializing SDL functionality
    SDL_Init(SDL_INIT_VIDEO);

    // Initializing SDL_ttf functionality
    TTF_Init();

    // Creating the window of the app
    SDL_Window *window = SDL_CreateWindow("Jumping Jett",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);

    /*
    Renderer is created to draw things on the window.
    */

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    printf("SDL Window created.\n");

    /*
    Creating 4 threads:
        1) jett Thread:
            a) Makes Jett move upward or downward
            b) Checks if jett has crashed against any obstacle
        
        2) Obstacle creator thread
            a) Creates an obstacle every 2 seconds
            b) Does nothing if there are already 3 obstacles in the game
        
        3) Obstacle mover thread
            a) Moves obstacle left through X axis
            b) Deletes an obstacle if it has reached the leftmost corner
            c) Counts deleted obstacles to generate score
        4) View Updater Thread
            a) Deals with all the drawing updates while the game is still running
    
    To create a thread from <windows.h>, we need an ID and a Handle.
    4 IDs and 4 handles bellow, for each of the above mentioned thread.
    */

    DWORD jettThreadId, obstacleCreatorThreadId, obstacleMoverThreadId, viewUpdaterThreadId;
    HANDLE jettThreadHandle, obstacleCreatorThreadHandle, obstacleMoverThreadHandle, viewUpdaterThreadHandle;

    //Initializing default state of the game.
    initGame();
    printf("Game initialized successfully\n");

    /*
    Creating all the views necessary for the UI
        1. The background image
        2. The Jett's poster
        3. Texts (App name, Team names etc)
        4. The start button
        5. Initial Score
        5. Create the Jett player
    */

    createAllViews(renderer);
    printf("Game views created\n");

    // Setting background color Pale Black
    SDL_SetRenderDrawColor(renderer, 35, 43, 43, 0xFF);
    SDL_RenderClear(renderer);

    // Drawing all the things that we have created
    drawBackgroundImage(renderer);
    drawJettPoster(renderer);
    drawAppDescription(renderer);
    drawStartButton(renderer);
    drawScoreText(renderer);
    drawScoreValue(renderer);

    SDL_RenderPresent(renderer);

    bool quit = false;
    while (!quit)
    {
        SDL_Event e;

        // Waiting for the next available event
        SDL_WaitEvent(&e);

        // User requests quit
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }

        // Clicking mouse
        else if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            // When user clicks inside the button area
            if (isStartButtonClicked(e))
            {
                printf("Start button has been clicked\n");

                if (isGameRunning())
                {
                    // STOP has been clicked. Killing all the 4 threads
                    TerminateThread(jettThreadHandle, 0);
                    TerminateThread(obstacleCreatorThreadHandle, 0);
                    TerminateThread(obstacleMoverThreadHandle, 0);
                    TerminateThread(viewUpdaterThreadHandle, 0);

                    // Updating game state variables
                    stopGame();

                    // Update=ing start button text as "START"
                    recreateStartButton(renderer, (char *)"START");
                    drawStartButton(renderer);
                }
                else
                {
                    startGame();

                    // Creating all the 4 threads
                    jettThreadHandle = CreateThread(
                        0,
                        0,
                        jettThread,
                        renderer,
                        0,
                        &jettThreadId);

                    obstacleCreatorThreadHandle = CreateThread(
                        0,
                        0,
                        obstacleCreatorThread,
                        renderer,
                        0,
                        &obstacleCreatorThreadId);

                    obstacleMoverThreadHandle = CreateThread(
                        0,
                        0,
                        obstacleMoverThread,
                        renderer,
                        0,
                        &obstacleMoverThreadId);

                    viewUpdaterThreadHandle = CreateThread(
                        0,
                        0,
                        viewUpdaterThread,
                        renderer,
                        0,
                        &viewUpdaterThreadId);

                    // Updating the start button as "STOP"
                    recreateStartButton(renderer, (char *)"STOP");
                    drawStartButton(renderer);
                }

                // Updating the screen
                SDL_RenderPresent(renderer);
            }
        }

        // Pressing any key
        else if (e.type == SDL_KEYDOWN)
        {
            // When the pressed key is SPACE bar
            if (e.key.keysym.sym == SDLK_SPACE)
            {
                if (isGameRunning())
                {
                    printf("Space bar pressed\n");

                    // Getting the pointer to the class "Player" and setting it as "jump mode"
                    Player *player = getPlayer();
                    player->startJump();
                }
            }
        }
    }

    // Destroying all the threads to free their memory as the program is ends.
    CloseHandle(jettThreadHandle);
    CloseHandle(obstacleCreatorThreadHandle);
    CloseHandle(obstacleMoverThreadHandle);
    CloseHandle(viewUpdaterThreadHandle);

    // Destroying all the view-related elements
    destroyAllViews();

    // Finally we free all the memory the SDL library took
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}