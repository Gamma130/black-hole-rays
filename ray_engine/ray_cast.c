#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "../ODE_solver/ODE_solver.h"
#include "ray_cast.h"

int sign_flip(double state[2][8])
{
    if (state[0][2] * state[1][2] < 0) {
        return 1;
    }
    return 0;
}

int hit_detection(double state[2][8], float dt, float radius)
{
    for (int c = 0; c < 10; c++){
        dt = 0.5 * dt;
        
        double state_prev[2][8];
        memcpy(state_prev, state, sizeof(double[2][8]));
        ODE_solver(state, dt);
        if (!sign_flip(state)) {
            for (int i = 0; i < 8; i++){
                state[0][i] = state[1][i];
                state[1][i] = state_prev[1][i];
            }
        }
    }

    if (state[0][1] < radius){
        return 1;
    }
    return 0;
}

int ray_cast(double state[2][8], float dt, float tmax, float radius)
{   
    //evolve state by dt until tmax is reached
    for(int i = 0; i <= tmax/dt; i++)
    {
        ODE_solver(state, dt);

        //  if radius smaller than 1: return 0
        if(state[1][1] <= 1)
        {   
            return 2;
        }
        
        //  if sign_flip: call hit_detection!
        if(state[0][2] * state[1][2] <= 0)
        {
            //  if hit: return 1
            if (hit_detection(state, dt, radius))
            {
                return 1;
            }
        }
        
    }

    // if no hit: return 0
    return 0;    
}