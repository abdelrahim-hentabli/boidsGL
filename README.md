# BoidsGL

## Dependencies

g++, CMake, OpenGL, and GLUT

### Installing Dependencies

On Ubuntu you can install all dependencies using the command  
### ```apt-get install g++ cmake libglu1-mesa-dev freeglut3-dev mesa-common-dev libomp-dev```

## Running the code

Once all dependencies are installed, go to the build subdirectory and run ```cmake ..```
and then, once cmake has completed, ```make``` 
can be run from the bin or build directories, with an output in the bin directory which can be run with ```./boids``` for a basic version of the main visual project.


Parameters can be changed using the options to the command with

```./boids <# of boids> <# threads> <seperation weight> <alignment weight> <cohesion weight> <obs avoidance weight>```

Timing and testing can be done with the  ```./timing``` and ```./timingMP``` command with usage  
```./timing(MP) <# of boids> <# of timesteps> <# of threads>\n```

## Current State
![Boids Preview](/imgs/boids_preview.gif?raw=true "Boids")
