#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include "gl_func.h"
#include "boids.h"

const int SCREEN_WIDTH = 768;
const int SCREEN_HEIGHT = 480;



int main(int argc, char** argv){
    // SDL_Window* gWindow = nullptr;
    // SDL_Renderer* gRenderer = nullptr;
    
    // init_sdl(SCREEN_WIDTH,SCREEN_HEIGHT,gWindow, gRenderer);
    // SDL_Delay(2000);

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