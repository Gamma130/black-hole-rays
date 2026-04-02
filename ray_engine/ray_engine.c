#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <cblas.h>
#include "../ODE_solver/ODE_solver.h"

int hit_detection(double state[2][8], float dt, float radius);
void convert_to_spherical(double state[8], double camera[3]);
void ray_engine(int px, double (*output)[px][8], double camera[3], double screen_dist);

double flat_speed(double vel[3])
{
    return pow(vel[0]*vel[0] + vel[1]*vel[1] + vel[2]*vel[2], 0.5);
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
            output[i][j][6] = yz_coord[i];
            //z-coordinate & z-velocity
            output[i][j][3] = yz_coord[j];
            output[i][j][7] = yz_coord[j];

            //normalize velocities (maybe do after converting to spherical?)
            double vel[3] = {output[i][j][5], output[i][j][6], output[i][j][7]};
            double speed = flat_speed(vel);
            output[i][j][5] = output[i][j][5] / speed;
            output[i][j][6] = output[i][j][6] / speed;
            output[i][j][7] = output[i][j][7] / speed;
        }
    }
}

void matrix_map(double matrix[3][3], double vector[3])
{   
    double vector_old[3] = {vector[0], vector[1], vector[2]};
    vector[0] = 0; vector[1] = 0; vector[2] = 0;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            vector[i] += matrix[i][j] * vector_old[j];
        }
    }
}

//converts a Cartesian state to (flat) spherical coordinates
void convert_to_spherical(double state[8], double camera[3])
{   
    //rotate about the y-axis to standard Cartesian coordinates
    double inc = camera[1] - 1.570;
    double Rotation[3][3] = {{cos(inc), 0, -sin(inc)}, {0, 1, 0}, {sin(inc), 0, cos(inc)}};
    double pos[3] = {state[1],state[2],state[3]};
    double vel[3] = {state[5],state[6],state[7]};
    matrix_map(Rotation, pos);
    matrix_map(Rotation, vel);

    //transform to (flat) spherical coordinates
    double r = pow(pos[0]*pos[0] + pos[1]*pos[1] + pos[2]*pos[2], 0.5);
    double theta = acos(pos[2] / r);
    double phi = pos[1] / fabs(pos[1]) * acos(pos[0] / pow(pos[0]*pos[0] + pos[1]*pos[1], 0.5));
    double Jacobian[3][3] = {
        {sin(theta)*cos(phi), sin(theta)*sin(phi), cos(theta)},
        {r*cos(theta)*cos(phi), r*cos(theta)*sin(phi), -r*sin(theta)},
        {-r*sin(theta)*sin(phi), r*sin(theta)*cos(phi), 0}};
    matrix_map(Jacobian, vel);

    //overwrite input state
    state[1] = r; state[2] = theta; state[3] = phi;
    state[5] = vel[0]; state[6] = vel[1]; state[7] = vel[2];
}

double curved_speed(double pos[3], double vel[3])
{
    double spatial_metric[3][3] = {
        {-1 / (1 - 1/pos[0]), 0, 0},
        {0, -pos[0]*pos[0], 0},
        {0, 0, -pos[0]*pos[0] * sin(pos[1])*sin(pos[1])}};
    
    double vel_0[3] = {vel[0], vel[1], vel[2]};
    matrix_map(spatial_metric, vel);

    return -vel_0[0]*vel[0] - vel_0[1]*vel[1] - vel_0[2]*vel[2];
}

void ray_engine(int px, double (*output)[px][8], double camera[3], double screen_dist)
{
    //generate initial rays in spherical coords
    cartesian_rays(px, output, camera, screen_dist);

    for(int i = 0; i < px; i++)
    {
        for(int j = 0; j < px; j++)
        {
            convert_to_spherical(output[i][j], camera);
        }
    }

    //set time components
    for(int i = 0; i < px; i++)
    {
        for(int j = 0; j < px; j++)
        {   
            output[i][j][0] = 0.0;

            //lightlike condition
            double pos[3] = {output[i][j][1], output[i][j][2], output[i][j][3]};
            double vel[3] = {output[i][j][5], output[i][j][6], output[i][j][7]};
            double speed = curved_speed(pos, vel);
            output[i][j][4] = pow(speed / (1 - 1/pos[0]), 0.5);
        }
    }
}