#ifndef SDL_FUNC_H
#define SDL_FUNC_H

#include <GL/glut.h>
#include "boids.h"
#include "vec.h"
#include "constants.h"

void init();
void display();
void draw_boids(boid* boids, int boids_count, float size);
void update();

void init(){

    the_boids = new boid[BOIDS_COUNT];
    srand(time(NULL));
    randomize_boids(the_boids, BOIDS_COUNT, WORLD_X_MIN, WORLD_X_MAX, WORLD_Y_MIN, WORLD_Y_MAX);

    // making background color black as first
    // 3 arguments all are 0.0
    glClearColor(1.0, 1.0, 1.0, 1.0);
     
    // making picture color green (in RGB mode), as middle argument is 1.0
    glColor3f(0.5, 0.75, 0.8);
     
    // breadth of picture boundary is 1 pixel
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
     
    // setting window dimension in X- and Y- direction
    gluOrtho2D(WORLD_X_MIN, WORLD_X_MAX, WORLD_Y_MIN, WORLD_Y_MAX);
}

void display(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    draw_boids(the_boids, BOIDS_COUNT, 1);
    
    glutSwapBuffers();
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

void update(){

    influence_boids(the_boids, BOIDS_COUNT, .01);
    move_boids(the_boids, BOIDS_COUNT, .01, WORLD_X_MIN, WORLD_X_MAX, WORLD_Y_MIN, WORLD_Y_MAX);
    glutPostRedisplay();
}

#endif //SDL_FUNC_H