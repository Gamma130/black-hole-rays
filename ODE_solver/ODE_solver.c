#include <unistd.h>
#include <stdio.h>
#include "ODE_function.h"
#include "ODE_solver.h"


void ODE_solver(double state[2][8], float dt);
void update(double state [2][8], float dt);
int ray_cast(double path[2][8], float dt, float tmax);


// take in an array of two arrays lenght 8 and buffer throught them
void ODE_solver(double state[2][8], float dt)
{  
    // rolling buffer
    for (int i = 0; i < 8; i++) {
        state[0][i] = state[1][i];
    }

    update(state, dt);
}

void update(double state[2][8], float dt){
    double dX[8];
    ODE_function(state[0], dX);

    for (int i = 0; i < 8; i++) {
        state[1][i] = state[0][i] + dt * dX[i]; //euler
    }
}