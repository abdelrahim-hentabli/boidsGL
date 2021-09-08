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
        boids[i].position += boids[i].direction * timeStep;
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
    //#pragma omp parallel for num_threads(BOIDS_COUNT)
    
    for(int i = 0; i < size; i++){
        
    }
}

//Rotation 165 degrees clockwise
//165 degrees ~= 2 Radians


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
        nose = center + (boids[i].direction * size);
        leftWing = center + (size * vec2(dot(rotationTransformL_1, boids[i].direction), dot(rotationTransformL_2, boids[i].direction)));
        rightWing = center + (size * vec2(dot(rotationTransformR_1, boids[i].direction), dot(rotationTransformR_2, boids[i].direction)));
        
        glBegin(GL_TRIANGLE_STRIP);

        glVertex2d(leftWing[0], leftWing[1]);
        glVertex2d(nose[0], nose[1]);
        glVertex2d(center[0], center[1]);
        glVertex2d(rightWing[0], rightWing[1]);
        
        glEnd(); 
    }
}

#endif //BOIDS_H