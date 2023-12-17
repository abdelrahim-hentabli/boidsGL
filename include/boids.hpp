#ifndef BOIDS_H
#define BOIDS_H

#include "vec.hpp"
#include <math.h>
#include <random>
#include <assert.h>
#include "constants.hpp"

struct boid{
    vec2 position;
    vec2 velocity;
    vec2 acceleration;
    
};

namespace {
    float randomFloat(float min, float max){
        float random = ((float) rand()) / (float) RAND_MAX;
        float diff = max-min;
        float r = random * diff;
        return min + r;
    }
}

void randomize_boids(boid* boids, int size, float x_min, float x_max, float y_min, float y_max){
    for(int i = 0; i < size; i++){
        boids[i].position = vec2(randomFloat(x_min, x_max), randomFloat(x_min, x_max));
        boids[i].velocity = (vec2(randomFloat(x_min, x_max), randomFloat(x_min, x_max)) - boids[i].position).normalize();
    }
}

void init_boids (boid* &boids, int size, float x_min, float x_max, float y_min, float y_max);
void move_boids (boid* boids, int size, double timeStep, float x_min, float x_max, float y_min, float y_max);
void influence_boids (boid* boids, int size, double timeStep);


#endif //BOIDS_H