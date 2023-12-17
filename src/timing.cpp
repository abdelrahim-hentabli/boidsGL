#include <iostream>
#include "boids.h"
#include "constants.hpp"

int main(int argc, char** argv){
    if(argc < 3){
        std::cout<<"Usage: timing(MP) <# of boids> <# of timesteps>\n";
        return 1;
    }
    int boid_amount = 1;
    int steps = 0;
    try{
        boid_amount = std::stoi(argv[1]);
        assert(boid_amount >0);
        steps = std::stoi(argv[2]);
    }
    catch(std::exception const &e){
        std::cout<<"Usage: timing(MP) <# of boids> <# of timesteps>\n";
        return 1;
    }
    if(argc == 4){
        try{
            threads = std::stoi(argv[3]);
            assert(threads >0);
        }
        catch(std::exception const &e){
            std::cout<<"Usage: timing(MP) <# of boids> <# of timesteps> <# of threads>(optional)\n";
            return 1;
        }
    }
    srand(42);
    float alignment_weight  = DEFAULT_ALIGNMENT_WEIGHT;
    float cohesion_weight   = DEFAULT_COHESION_WEIGHT;
    float seperation_weight = DEFAULT_SEPERATION_WEIGHT;
    float obs_aviod_weight  = DEFAULT_OBS_AVOID_WEIGHT
    boid* boids = new boid[boid_amount];
    randomize_boids(boids, boid_amount, WORLD_X_MIN, WORLD_X_MAX, WORLD_Y_MIN, WORLD_Y_MAX);
    for(int i = 0; i < steps; i++){
        influence_boids(boids, boid_amount, 1);
        move_boids(boids, boid_amount, 1, WORLD_X_MIN, WORLD_X_MAX, WORLD_Y_MIN, WORLD_Y_MAX);
    }
    std::cout<<"Position:     "<<boids[0].position<<'\n'<<"Direction:    "<<boids[0].velocity<<'\n'<<"Acceleration: "<<boids[0].acceleration<<"\n\n";
    return 0;
}