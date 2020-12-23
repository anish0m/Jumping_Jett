#include <stdio.h>
#include <SDL.h>
#include "jumpingjett-view.h"
using namespace  std;

int main(int argc, char* argv[])
{
    // Unused argc, argv
    (void) argc;
    (void) argv;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Jumping Jett",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    // Create renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface *backgroundImg = NULL;
    SDL_Surface *jettImg = NULL;

    SDL_Texture *texture = NULL;

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

        // Initialize renderer color black for the background
        SDL_SetRenderDrawColor(renderer, 35, 43, 43, 0xFF);
        // Clear screen
        SDL_RenderClear(renderer);

        drawBackgroundImage(renderer, backgroundImg, texture);
        drawJettPoster(renderer, jettImg, texture);

        // Update screen
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(backgroundImg);
    SDL_FreeSurface(jettImg);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}