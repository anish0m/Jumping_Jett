#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "dimensions.h"
#include "view.h"
#include "game.h"
#include <windows.h>

using namespace std;

int main(int argc, char *argv[])
{
    // Unused argc, argv
    (void)argc;
    (void)argv;

    // Initialize SDL functionality
    SDL_Init(SDL_INIT_VIDEO);

    // Initialize SDL_ttf functionality
    TTF_Init();

    // Create the window of the app
    SDL_Window *window = SDL_CreateWindow("Jumping Jett",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, // dimensions of the window
                                          SDL_WINDOW_SHOWN);

    /*
    Renderer is created. A renderer can draw things on the window. That's why it is useful
    */
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    printf("SDL Window created\n");

    /*****************************************************************************************
    We have to create 4 threads:
        1) jett Thread:
            a) Makes Jett move upward or downward
            b) Checks if jett has crashed against any obstacle
        
        2) Obstacle creator thread
            a) Creates an obstacle every 2 seconds
            b) Does nothing if there are already 3 obstacles in the game
        
        3) Obstacle mover thread
            a) Moves obstacle left through X axis
            b) Deletes an obstacle if it has reached the leftmost corner
    
    To create a thread from <windows.h>, we need an ID and a Handle. Thats why we have 4 IDs and
    4 handles bellow, for each of the above mentioned thread. 
    */
    DWORD jettThreadId, obstacleCreatorThreadId, obstacleMoverThreadId, viewUpdaterThreadId;
    HANDLE jettThreadHandle, obstacleCreatorThreadHandle, obstacleMoverThreadHandle, viewUpdaterThreadHandle;

    /* Initialize default state of the game. */
    initGame();
    printf("Game initialized successfully\n");

    /*
    Create all the views necessary for the UI
        1. Create the background image
        2. Create the Jett's poster
        3. Create texts (App name, Team names etc)
        4. Create the start button
        5. Create the Jett player
    
    Important note: 
    "Create" DOES NOT mean "Draw". It just means loading the necessary things before drawing any object.
    */
    createAllViews(renderer);
    printf("Game views created\n");

    // Set background color Black
    SDL_SetRenderDrawColor(renderer, 35, 43, 43, 0xFF);
    SDL_RenderClear(renderer);

    // Draw all the things that we have created
    drawBackgroundImage(renderer);
    drawJettPoster(renderer);
    drawAppDescription(renderer);
    drawStartButton(renderer);

    /*
    Drawings will not be visible until you call this function. It means "Refresh"
    */
    SDL_RenderPresent(renderer);

    bool quit = false;
    while (!quit)
    {
        SDL_Event e;

        // Wait for the next available event
        SDL_WaitEvent(&e);

        // User requests quit
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }

        // User clicks with the mouse anywhere in the app
        else if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            // When user clicks inside the button area
            if (isStartButtonClicked(e))
            {
                printf("Start button has been clicked\n");

                if (isGameRunning())
                {
                    // STOP has been clicked. So, kill all the 4 threads
                    TerminateThread(jettThreadHandle, 0);
                    TerminateThread(obstacleCreatorThreadHandle, 0);
                    TerminateThread(obstacleMoverThreadHandle, 0);
                    TerminateThread(viewUpdaterThreadHandle, 0);

                    // Update game state variables
                    stopGame();

                    // Update start button text as "START"
                    recreateStartButton(renderer, (char *)"START");
                    drawStartButton(renderer);
                }
                else
                {
                    // Modify game state variables to indicate that game has started
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

                    // Update the start button as "STOP"
                    recreateStartButton(renderer, (char *)"STOP");
                    drawStartButton(renderer);
                }

                // Update the screen
                SDL_RenderPresent(renderer);
            }
        }

        // User has pressed any key
        else if (e.type == SDL_KEYDOWN)
        {
            // User has pressed SPACE bar
            if (e.key.keysym.sym == SDLK_SPACE)
            {
                if (isGameRunning())
                {
                    printf("Space bar pressed\n");

                    // Get the pointer to the jett player and set it as "jump mode"
                    Player *player = getPlayer();
                    player->startJump();
                }
            }
        }
    }

    // When the program is ending, destroy all the threads and free their memory
    CloseHandle(jettThreadHandle);
    CloseHandle(obstacleCreatorThreadHandle);
    CloseHandle(obstacleMoverThreadHandle);
    CloseHandle(viewUpdaterThreadHandle);

    // Free all the memory that the view elements took when creating
    destroyAllViews();

    // Free all the memory the SDL library took
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}