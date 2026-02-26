#include <unistd.h>
#include <stdio.h>
#include "ODE_function.h"


void ODE_solver(double path[2][8], float dt);

int main(void)
{
    double X[8] = {0.0, 2.0, 0.1, 0.1, 0.5, 0.1, 0.0, 0.0};
    double output[8];
    double path[2][8] = {
        {0.0, 2.0, 0.1, 0.1, 0.5, 0.1, 0.0, 0.0},
        {0.0, 2.0, 0.1, 0.1, 0.5, 0.1, 0.0, 0.0}
    };

    ODE_function(X, output);
    printf("Elements of the array are: ");

    float dt = 0.1;
    ODE_solver(path, dt);

    //int length = sizeof(output) / sizeof(output[0]);
    //for (int i = 0; i < length; i++) {
    //    printf("%f ", output[i]); 
    //}
    printf("\n");
    for (int i = 0; i < 8; i++) {
        printf("%f ", path[0][i]);
    }
    printf("\n");
    for (int i = 0; i < 8; i++) {
        printf("%f ", path[1][i]);
    }
    return 0;
}

// take in an array of two arrays lenght 8 and buffer throught them
void ODE_solver(double path[2][8], float dt)
{   
    double dX[8];
    ODE_function(path[0], dX);

    for (int i = 0; i < 8; i++) {
        path[0][i] = path[1][i];
        path[1][i] = path[0][i] + dt * dX[i]; //euler
    }
}