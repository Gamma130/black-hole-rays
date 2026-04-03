#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "./ray_engine/ray_engine.h"
#include "./display/display.h"
#include "./ray_engine/ray_cast.h"

int main(void)
{   
    //generate initial rays with ray_engine(px, output, camera, screen_dist)

    int px = 300;
    double camera[3] = {2.5, 1.5, 0};
    double screen_dist = 0.1;
    double output[px][px][8];
    ray_engine(px, output, camera, screen_dist);

    //evolve every ray with ray_cast(double state[2][8], float dt, float tmax, float radius)

    double dt = 0.004;
    double tmax = 5.0;
    double radius = 1.26;

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

    display(px, ray_img);

    return 0;
}