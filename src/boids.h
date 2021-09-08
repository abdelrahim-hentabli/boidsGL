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
    srand(time(NULL));
    for(int i = 0; i < size; i++){
        boids[i].position = vec2(randomFloat(x_min, x_max), randomFloat(x_min, x_max));
        boids[i].direction = (vec2(randomFloat(x_min, x_max), randomFloat(x_min, x_max)) - boids[i].position).normalize();
    }
}

void move_boids(boid* boids, int size, double timeStep, float x_min, float x_max, float y_min, float y_max){
    //#pragma omp parallel for num_threads(BOIDS_COUNT)
    for(int i = 0; i < size; i++){
    
        boids[i].direction += boids[i].acceleration * timeStep;
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
    vec2 flockHeading;
    vec2 flockCenter;
    vec2 seperation;
    
    int neighbors;
    int avoidNeighbors;

    vec2 vecToNeighbor;
    
    //#pragma omp parallel for num_threads(BOIDS_COUNT) private(flockHeading, flockCenter, seperation, neighbors, vecToNeighbor, avoidNeighbors)
    for(int i = 0; i < size; i++){
        neighbors = 0;
        avoidNeighbors = 0;
        flockHeading = {0,0};
        flockCenter = {0,0};
        seperation = {0,0};
        boids[i].acceleration = {0, 0};

        for(int j = 0; j < size; j++){
            if(i != j){
                vecToNeighbor = boids[j].position - boids[i].position;
                if(vecToNeighbor.magnitude() < BOID_VIEW_DIST_SQR){
                    if(acos(dot(boids[i].direction, vecToNeighbor) / boids[i].direction.magnitude() / vecToNeighbor.magnitude()) <= BOID_VIEW_ANGLE_RADIANS){
                        neighbors++;
                        flockHeading += boids[j].direction;
                        flockCenter += boids[j].position;
                        if(vecToNeighbor.magnitude() < BOID_AVOID_DIST_SQR){
                            avoidNeighbors++;
                            seperation -= vecToNeighbor / vecToNeighbor.magnitude();
                        }
                    }
                }
            }
            if(neighbors > 0){
                vec2 alignmentForce = (flockHeading / neighbors);
                if(alignmentForce.magnitude() > .3){
                    alignmentForce = alignmentForce.normalize() * .2;
                }
                boids[i].acceleration += ALIGNMENT_WEIGHT * (flockHeading / neighbors);
                vec2 cohesionForce = ((flockCenter / neighbors) -boids[i].position);
                if(cohesionForce.magnitude() > .3){
                    cohesionForce = cohesionForce.normalize() * .2;
                }
                boids[i].acceleration += COHESION_WEIGHT * cohesionForce;
                if(avoidNeighbors > 0){
                    vec2 seperationForce = ((seperation / avoidNeighbors) - boids[i].direction);
                    if(seperationForce.magnitude() > .4 ){
                        seperationForce = seperationForce.normalize() * .2;
                    }
                    boids[i].acceleration += SEPERATION_WEIGHT * seperationForce;
                }
            }
            // if(boids[i].position[0] - WORLD_X_MIN < OBS_AVOID_DIST){
            //     boids[i].acceleration[0] += OBS_AVOID_WEIGHT * OBS_AVOID_DIST / (boids[i].position[0] - WORLD_X_MIN);
            // }
            // else if(WORLD_X_MAX - boids[i].position[0] < OBS_AVOID_DIST){
            //     boids[i].acceleration[0] += OBS_AVOID_WEIGHT * OBS_AVOID_DIST /(boids[i].position[0] - WORLD_X_MAX);
            // }
            // if(boids[i].position[1] - WORLD_Y_MIN < OBS_AVOID_DIST){
            //     boids[i].acceleration[1] += OBS_AVOID_WEIGHT * OBS_AVOID_DIST /(boids[i].position[1] - WORLD_Y_MIN);
            // }
            // else if(WORLD_Y_MAX - boids[i].position[1] < OBS_AVOID_DIST){
            //     boids[i].acceleration[1] += OBS_AVOID_WEIGHT * OBS_AVOID_DIST /(boids[i].position[1] - WORLD_Y_MAX);
            // }
        }
    }
}


void draw_boids(boid* boids, int boids_count, float size){
    vec2 center;
    vec2 nose;
    vec2 leftWing; 
    vec2 rightWing;
    vec2 rotationTransformL_1 = {cos(BOID_DRAW_ANGLE_RADIANS), -sin(BOID_DRAW_ANGLE_RADIANS)};
    vec2 rotationTransformL_2 = {sin(BOID_DRAW_ANGLE_RADIANS), cos(BOID_DRAW_ANGLE_RADIANS)};
    vec2 rotationTransformR_1 = {cos(-BOID_DRAW_ANGLE_RADIANS), -sin(-BOID_DRAW_ANGLE_RADIANS)};
    vec2 rotationTransformR_2 = {sin(-BOID_DRAW_ANGLE_RADIANS), cos(-BOID_DRAW_ANGLE_RADIANS)};
    
    
    for(int i = 0; i < boids_count; i++){
        center = boids[i].position;
        nose = center + (boids[i].direction * size).normalize();
        leftWing = center + (size * .75 * vec2(dot(rotationTransformL_1, boids[i].direction), dot(rotationTransformL_2, boids[i].direction)).normalize());
        rightWing = center + (size * .75 * vec2(dot(rotationTransformR_1, boids[i].direction), dot(rotationTransformR_2, boids[i].direction)).normalize());
        
        glBegin(GL_TRIANGLE_STRIP);

        glVertex2d(leftWing[0], leftWing[1]);
        glVertex2d(nose[0], nose[1]);
        glVertex2d(center[0], center[1]);
        glVertex2d(rightWing[0], rightWing[1]);
        
        glEnd(); 
    }
}

#endif //BOIDS_H