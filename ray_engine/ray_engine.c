#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "../ODE_solver/ODE_solver.h"

int hit_detection(double state[2][8], float dt, float radius);

int main(void)
{
    double state_1[2][8] = {
        {0.0, 1.5, 0.1, 0.1, 0.1, 0.0, -0.5, 0.0},
        {0.0, 1.5, 0.1, 0.1, 0.1, 0.0, -0.5, 0.0}
    };

    double state_2[2][8] = {
        {0.0, 2.0, 0.1, 0.1, 0.1, -0.5, 0.0, 0.0},
        {0.0, 2.0, 0.1, 0.1, 0.1, -0.5, 0.0, 0.0}
    };

    double state_3[2][8] = {
        {0.0, 2.0, 0.1, 0.1, 0.1, 0.5, 0.0, 0.0},
        {0.0, 2.0, 0.1, 0.1, 0.1, 0.5, 0.0, 0.0}
    };

    float dt = 0.1;
    float tmax = 10;
    float radius = 2.0;

    if(ray_cast(state_1, dt, tmax, radius) == 1) {
        printf("Discooo \n");
    } else {
        printf("no lights, no music \n");
    }
    if(ray_cast(state_2, dt, tmax, radius) == 2) {
        printf("Black Hole tiime.\n");
    } else {
        printf("black hole sun wont you come \n");
    }
    if(ray_cast(state_3, dt, tmax, radius) == 0) {
        printf("Buh-bye");
    } else {
        printf("why arent you running");
    }

    return 0;
}

void cartesian_rays(int px, double output[px][px][8], double camera[3], double screen_dist)
{
    //determine screen size & pixel size
    double screen_size = 2 * screen_dist; //assuming fov of 90 degrees
    double pixel_size = screen_size / (double)px;

    //determine pixel center locations
    double x_coord = camera[0] - screen_dist;
    double yz_coord[px];
    for(int i = 0; i < px; i++)
    {
        yz_coord[i] = (double)i * pixel_size - screen_size / 2.0 + pixel_size / 2.0;
    }

    for(int i = 0; i < px; i++)
    {
        for(int j = 0; j < px; j++)
        {
            //x-coordinate & x-velocity
            output[i][j][1] = x_coord;
            output[i][j][5] = x_coord - camera[0];
            //y-coordinate & y-velocity
            output[i][j][2] = yz_coord[i];
            output[i][j][6] = yz_coord[i] - camera[1];
            //z-coordinate & z-velocity
            output[i][j][3] = yz_coord[j];
            output[i][j][7] = yz_coord[j] - camera[2];
        }
    }

}

void convert_to_spherical(int px, double output[px][px][8], double camera[3])
{
    //convert to (flat) spherical coordinates
}

double calculate_speed(double vel_x, double vel_y, double vel_z) //should be curved ST version!
{
    return pow(vel_x*vel_x + vel_y*vel_y + vel_z*vel_z, 0.5);
}

void ray_engine(int px, double output[px][px][8], double camera[3], double screen_dist)
{
    //cartesian_rays(double camera[3], double screen_dist)

    //convert_to_spherical(int px, double output[px][px][8], double camera[3])
    
    //normalize velocities & make them lightlike

    //double speed = calculate_speed(output[i][j][5], output[i][j][6], output[i][j][7]);
    
    //output[i][j][5] = output[i][j][5] / speed;
    //output[i][j][6] = output[i][j][6] / speed;
    //output[i][j][7] = output[i][j][7] / speed;
}