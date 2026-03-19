#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "./ray_engine/ray_engine.h"
#include "./display/display.h"

int main(void)
{
    //ERROR -nan 1.572330 2.898045 2.067561 1.000000 -0.156824 -0.336917 0.037421
    //generate initial rays with ray_engine(px, output, camera, screen_dist)
    //evolve every ray with ray_cast(double state[2][8], float dt, float tmax, float radius)
    //display with display(int px, bool grid[px][px])
    
    int px = 3;
    double camera[3] = {2, 0.1, 0};
    double screen_dist = 0.5;
    double output[px][px][8];
    ray_engine(px, output, camera, screen_dist);

    for(int i = 0; i < px; i++)
    {
        for(int j = 0; j < px; j++)
        {
            for(int k = 0; k < 8; k++)
            {
                printf("%f ", output[i][j][k]); 
            }
            printf("\n");
        }
    }

    int pixel = 100;
    bool grid[pixel][pixel];

    // example data
    for (int y = 0; y < pixel; y++)
        for (int x = 0; x < pixel; x++)
            grid[y][x] = (x + y) % 2;
    display(pixel, grid);

    return 0;
}