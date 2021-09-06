#include <iostream>
#include "SDL.h"
#include "sdl_func.h"
#include "boids.h"

int main(){
    SDL_Window* gWindow = nullptr;
    SDL_Surface* gScreenSurface = nullptr;
    init_sdl(640,640,gWindow, gScreenSurface);
    SDL_Delay(2000);

    boid theBoid = {vec2(5.0,5.0), vec2(1.0,1.0)}
    

    bool cont = true;
    SDL_Event e;
    while(cont){
        //Handle Events
        while(SDL_PollEvent(&e) != 0){
            switch(e.type){
                case SDL_QUIT:
                    cont = false;
                    break;
                default:
                    break;
            }
        }

    }

    quit_sdl(gWindow);
    
    return 0;
}