#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include "gl_func.h"
#include "boids.h"
#include "constants.h"


int main(int argc, char** argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
     
    // giving window size in X- and Y- direction
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(0, 0);
     
    // Giving name to window
    glutCreateWindow("Boids");
    
    glutIdleFunc(update);
    
    glutDisplayFunc(display);
    
    init();
    
    glutMainLoop();

    return 0;
}