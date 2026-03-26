#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "./ray_engine/ray_engine.h"
#include "./display/display.h"
#include "./ray_engine/ray_cast.h"

int main(void)
{   
    //generate initial rays with ray_engine(px, output, camera, screen_dist)

    int px = 3;
    double camera[3] = {2.5, 1.5, 0};
    double screen_dist = 0.1;
    double output[px][px][8];
    ray_engine(px, output, camera, screen_dist);

    for(int i = 0; i < px; i++)
    {
        for(int j = 0; j < px; j++)
        {   
            for(int k = 0; k < 8; k++)
            {
                printf("%f, ", output[i][j][k]);
            }
            printf("\n");
        }
    }

    //evolve every ray with ray_cast(double state[2][8], float dt, float tmax, float radius)
    double dt = 0.001;
    double tmax = 10.0;
    double radius = 1.3;

    int ray_img[px][px];
    for(int i = 0; i < px; i++)
    {
        for(int j = 0; j < px; j++)
        {   
            double state[2][8];
            for(int k = 0; k < 8; k++)
            {
                state[1][k] = output[i][j][k];
            }
            ray_img[i][j] = ray_cast(state, dt, tmax, radius);
        }
    }

    //display(px, ray_img);

    return 0;
}