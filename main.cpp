#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "view.h"
#include "game.h"
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

    initGame();
    printf("Game initialized successfully\n");

    createAllViews(renderer);
    printf("Game views created\n");

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
                    destroyPlayerView();
                    stopGame();
                }
                else
                {
                    startGame();
                    createPlayerView(renderer);
                }
                redrawStartButton(renderer);
            }
        }

        // Set background color Black
        SDL_SetRenderDrawColor(renderer, 35, 43, 43, 0xFF);
        SDL_RenderClear(renderer);

        // Draw background image, jet image
        drawBackgroundImage(renderer);
        drawJettPoster(renderer);
        drawAppDescription(renderer);
        drawStartButton(renderer);

        // Draw game
        if (isGameRunning())
        {
            Player* player = getPlayer();
            drawPlayer(renderer, player->percentX, player->percentY);
        }

        // Update screen
        SDL_RenderPresent(renderer);
    }
    destroyAllViews();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}