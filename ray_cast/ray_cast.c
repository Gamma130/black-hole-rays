#include <unistd.h>
#include <stdio.h>
#include <string.h> 
#include "../ODE_solver/ODE_solver.h"

int hit_detection(double state[2][8], float dt, float radius);

int main(void)
{
    //double X[8] = {0.0, 2.0, 0.1, 0.1, 0.5, 0.1, 0.0, 0.0};
    //double output[8];
    double state1[2][8] = {
        {0.0, 2.0, 0.1, 0.1, 0.1, 0.0, -1.1, 0.0},
        {0.01, 2.0, -0.01, 0.1, 0.1, 0.120938, -1.1, 0.0}
    };

    double state[2][8] = {
        {0.0, 2.0, 0.1, 0.1, 0.1, 0.0, 0.0, 0.0},
        {0.0, 2.0, 0.1, 0.1, 0.1, 0.0, 0.0, 0.0}
    };

    float dt = 0.1;
    ODE_solver(state, dt);

    //int length = sizeof(output) / sizeof(output[0]);
    //for (int i = 0; i < length; i++) {
    //    printf("%f ", output[i]); 
    //}
    printf("\n");
    for (int i = 0; i < 8; i++) {
        printf("%f ", state[0][i]);
    }
    printf("\n");
    for (int i = 0; i < 8; i++) {
        printf("%f ", state[1][i]);
    }
    printf("\n %i", hit_detection(state, dt, 3));
    return 0;
}

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

int ray_cast(double state[2][8], float dt, float tmax)
{   
    //evolve state by dt until tmax is reached
    //at every step:
    //  if sign_flip: call hit_detection!
    //  if hit: return 1
    //  if radius smaller than 1: return 0
    //return 0
    
    // ODE_solver (update)
    // Result Buffer State[0], State[1]
    // Check if State[1] has a differnt sign then State[0]
    // If yes and tolerance to small
    // role back state[0] state[1]
    // repeat update untill tolerance small enough
    // brake safty???
    
    return 0;
}