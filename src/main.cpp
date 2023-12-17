#include <iostream>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "gl_func.hpp"
#include "boids.hpp"
#include "constants.hpp"

int main(int argc, char** argv){
    if(argc == 7){
        try{
            BOIDS_COUNT = std::stoi(argv[1]);
            assert(BOIDS_COUNT > 0);
            threads = std::stoi(argv[2]);
            assert(threads > 0);
            SEPERATION_WEIGHT = std::stof(argv[3]);
            ALIGNMENT_WEIGHT = std::stof(argv[4]);
            COHESION_WEIGHT = std::stof(argv[5]);
            OBS_AVOID_WEIGHT = std::stof(argv[6]);
            
        }
        catch(std::exception const &e){
            std::cout<<"Usage: ./boids <# of boids> <# threads> <seperation weight> <alignment weight> <cohesion weight> <obs avoidance weight>\n";
            return 1;
        }
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
     
    // giving window size in X and Y direction
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
