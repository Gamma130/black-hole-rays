#include <SDL2/SDL.h>
#include <stdbool.h>
#include "./display.h"


void display(int px, int grid[px][px])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
        "Grid",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        px * CELL,
        px * CELL,
        0
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Event e;
    bool running = true;

    while (running)
    {
        while (SDL_PollEvent(&e))
            if (e.type == SDL_QUIT)
                running = false;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int y = 0; y < px; y++)
        {
            for (int x = 0; x < px; x++)
            {
                if (grid[y][x])
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                else
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_Rect r = {
                    x * CELL,
                    y * CELL,
                    CELL,
                    CELL
                };

                SDL_RenderFillRect(renderer, &r);
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
}