#ifndef SDL_FUNC_H
#define SDL_FUNC_H

#include <GL/glut.h>
#include "boids.h"
#include "vec.h"
#include "constants.h"

int count = 0;

void init(){

    the_boids = new boid[BOIDS_COUNT];
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
    
    draw_boids(the_boids, BOIDS_COUNT, .5);
    
    glutSwapBuffers();
}

void update(){
    
    influence_boids(the_boids, BOIDS_COUNT, .01);
    move_boids(the_boids, BOIDS_COUNT, .01, WORLD_X_MIN, WORLD_X_MAX, WORLD_Y_MIN, WORLD_Y_MAX);
    glutPostRedisplay();
}

#endif //SDL_FUNC_H