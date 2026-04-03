#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "./display.h"


void rotate_image(int px, int grid[px][px]){
    for (int i = 0; i < px; i++) {
        for (int j = i + 1; j < px; j++) {
            int temp = grid[i][j];
            grid[i][j] = grid[j][i];
            grid[j][i] = temp;
        }
    }
}

void display(int px, int grid[px][px])
{
    rotate_image(px, grid);
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    int width = px * CELL;
    int height = px * CELL;

    SDL_Window *window = SDL_CreateWindow(
        "",
        0,
        0,
        width,
        height,
        SDL_WINDOW_HIDDEN
    );

    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture *target =
        SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_RGBA32,
            SDL_TEXTUREACCESS_TARGET,
            width,
            height
        );

    SDL_SetRenderTarget(renderer, target);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for (int y = 0; y < px; y++)
    {
        for (int x = 0; x < px; x++)
        {
            if (grid[y][x] == 1)
                SDL_SetRenderDrawColor(renderer, 217, 79, 0, 255);
            else if(grid[y][x] == 2)
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

    SDL_Surface *surface =
        SDL_CreateRGBSurfaceWithFormat(
            0,
            width,
            height,
            32,
            SDL_PIXELFORMAT_RGBA32
        );

    SDL_RenderReadPixels(
        renderer,
        NULL,
        SDL_PIXELFORMAT_RGBA32,
        surface->pixels,
        surface->pitch
    );

    IMG_SavePNG(surface, "grid.png");

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(target);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
}