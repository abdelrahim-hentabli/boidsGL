#ifndef BOIDS_H
#define BOIDS_H

#include "vec.h"

struct boid{
    vec2 position;
    vec2 direction;
    
};

void move_boids(boid* boids, int size, double timeStep){
    for(int i = 0; i < size; i++){
        boids[i].position += boids[i].direction * timeStep;
    }
}

void influence_boids(boid* boids, int size, double timeStep){

}


#endif //BOIDS_H