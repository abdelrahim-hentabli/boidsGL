#ifndef SDL_FUNC_H
#define SDL_FUNC_H

int init_sdl(int screenWidth, int screenHeight, SDL_Window* gWindow, SDL_Surface* gScreenSurface){
    if( SDL_Init(SDL_INIT_VIDEO) < 0){
        return 1;
    }
    else{
        gWindow = SDL_CreateWindow("boids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
        if(gWindow == NULL){
            return 2;
        }
        else{
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return 0;
}

void quit_sdl(SDL_Window* gWindow){
    //Destroy Window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}
#endif //SDL_FUNC_H