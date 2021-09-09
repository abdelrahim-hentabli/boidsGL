#ifndef BOIDS_H
#define BOIDS_H

#include "vec.h"
#include <math.h>
#include <random>
#include <assert.h>
#include "constants.h"

struct boid{
    vec2 position;
    vec2 direction;
    vec2 acceleration;
    
};

float randomFloat(float min, float max){
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = max-min;
    float r = random * diff;
    return min + r;
}

void randomize_boids(boid* boids, int size, float x_min, float x_max, float y_min, float y_max){
    for(int i = 0; i < size; i++){
        boids[i].position = vec2(randomFloat(x_min, x_max), randomFloat(x_min, x_max));
        boids[i].direction = (vec2(randomFloat(x_min, x_max), randomFloat(x_min, x_max)) - boids[i].position).normalize();
    }
}

void move_boids(boid* boids, int size, double timeStep, float x_min, float x_max, float y_min, float y_max){
    #ifdef _OPENMP
    #pragma omp parallel for num_threads(threads)
    #endif
    for(int i = 0; i < size; i++){
    
        boids[i].direction += (boids[i].acceleration * timeStep);
        if(boids[i].direction.magnitude() > 1.5){
            boids[i].direction = boids[i].direction.normalize() * 1.5;
        }
        else if(boids[i].direction.magnitude() < .5){
            boids[i].direction = boids[i].direction.normalize() * .5;
        }
        boids[i].position += boids[i].direction * timeStep;

        //if off edge of screen, go to other side of screen
        if(boids[i].position[0] < x_min){
            boids[i].position[0] = x_max - (x_min - boids[i].position[0]);
        }
        else if(boids[i].position[0] > x_max){
            boids[i].position[0] = x_min + (boids[i].position[0] - x_max);
        }
        if(boids[i].position[1] < y_min){
            boids[i].position[1] = y_max - (y_min - boids[i].position[1]);
        }
        else if(boids[i].position[1] > y_max){
            boids[i].position[1] = y_min + (boids[i].position[1] - y_max);
        }
    }
}

void influence_boids(boid* boids, int size, double timeStep){
    
    #ifdef _OPENMP
    #pragma omp parallel for num_threads(threads)
    #endif
    for(int i = 0; i < size; i++){
        
        vec2 flockHeading = {0,0};
        vec2 flockCenter= {0,0};
        vec2 seperation= {0,0};
    
        int neighbors = 0;

        vec2 vecToNeighbor= {0,0};
        boids[i].acceleration = {0, 0};

        for(int j = 0; j < size; j++){
            if(i != j){
                vecToNeighbor = boids[j].position - boids[i].position;
                if(vecToNeighbor.magnitude() < BOID_VIEW_DIST){
                    if(acos(dot(boids[i].direction, vecToNeighbor) / boids[i].direction.magnitude() / vecToNeighbor.magnitude()) <= BOID_VIEW_ANGLE_RADIANS){
                        neighbors++;
                        flockHeading += boids[j].direction;
                        flockCenter += boids[j].position;
                        if(vecToNeighbor.magnitude() < BOID_AVOID_DIST){
                            seperation -= vecToNeighbor.normalize();
                        }
                    }
                }
            }
            if(neighbors > 0){
                //Alignment Force
                vec2 alignmentForce = (flockHeading / neighbors);
                if(alignmentForce.magnitude() > 1){
                    alignmentForce = alignmentForce.normalize();
                }
                boids[i].acceleration += ALIGNMENT_WEIGHT * (flockHeading / neighbors);

                //Cohesion Force
                vec2 cohesionForce = ((flockCenter / neighbors) -boids[i].position);
                if(cohesionForce.magnitude() > 1){
                    cohesionForce = cohesionForce.normalize();
                }
                boids[i].acceleration += COHESION_WEIGHT * cohesionForce;
                
                //Seperation Force
                vec2 seperationForce = (seperation + boids[i].direction);
                if(seperationForce.magnitude() > 1){
                    seperationForce = seperationForce.normalize();
                }
                boids[i].acceleration += SEPERATION_WEIGHT * seperationForce;
                
            }
            if(boids[i].position[0] - WORLD_X_MIN < OBS_AVOID_DIST){
                boids[i].acceleration[0] += OBS_AVOID_WEIGHT * OBS_AVOID_DIST / (boids[i].position[0] - WORLD_X_MIN);
            }
            else if(WORLD_X_MAX - boids[i].position[0] < OBS_AVOID_DIST){
                boids[i].acceleration[0] += OBS_AVOID_WEIGHT * OBS_AVOID_DIST /(boids[i].position[0] - WORLD_X_MAX);
            }
            if(boids[i].position[1] - WORLD_Y_MIN < OBS_AVOID_DIST){
                boids[i].acceleration[1] += OBS_AVOID_WEIGHT * OBS_AVOID_DIST /(boids[i].position[1] - WORLD_Y_MIN);
            }
            else if(WORLD_Y_MAX - boids[i].position[1] < OBS_AVOID_DIST){
                boids[i].acceleration[1] += OBS_AVOID_WEIGHT * OBS_AVOID_DIST /(boids[i].position[1] - WORLD_Y_MAX);
            }
            if(!double_equality(boids[i].acceleration.magnitude(), 0.0)){
                boids[i].acceleration.normalize();
            }
        }
    }
}


#endif //BOIDS_H