#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include "gl_func.h"
#include "boids.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

const float WORLD_X_MIN = -20;
const float WORLD_X_MAX = 20;

const float WORLD_Y_MIN = -20;
const float WORLD_Y_MAX = 20;


int main(int argc, char** argv){
    // SDL_Window* gWindow = nullptr;
    // SDL_Renderer* gRenderer = nullptr;
    
    // init_sdl(SCREEN_WIDTH,SCREEN_HEIGHT,gWindow, gRenderer);
    // SDL_Delay(2000);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
     
    // giving window size in X- and Y- direction
    glutInitWindowSize(1366, 768);
    glutInitWindowPosition(0, 0);
     
    // Giving name to window
    glutCreateWindow("Circle Drawing");
    myInit();
     
    glutDisplayFunc(display);
    glutMainLoop();

    boid theBoid = {vec2(640/2,640/2), vec2(1.0,1.0).normalize()};

    // bool cont = true;
    // SDL_Event e;
    // while(cont){
    //     //Handle Events
    //     while(SDL_PollEvent(&e) != 0){
    //         switch(e.type){
    //             case SDL_QUIT:
    //                 cont = false;
    //                 break;
    //             default:
    //                 break;
    //         }
    //     }
    //     draw_boids_sdl(gWindow, gRenderer, &theBoid, 1, 5, SCREEN_WIDTH, SCREEN_HEIGHT, WORLD_X_MIN, WORLD_X_MAX, WORLD_Y_MIN, WORLD_Y_MAX);
    //     influence_boids(&theBoid, 1, .017);
    //     move_boids(&theBoid, 1, .017);

    // }

    // quit_sdl(gWindow);
    
    return 0;
}