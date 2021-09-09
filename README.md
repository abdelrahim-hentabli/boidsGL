# BoidsGL

## Dependencies

g++, CMake, OpenGL, and GLUT

### Installing Dependencies

On Ubuntu you can install all dependencies using the command  
### ```apt-get install g++ cmake libglu1-mesa-dev freeglut3-dev mesa-common-dev libomp-dev```

## Running the code

Once all dependencies are installed, go to the build subdirectory and run ```cmake ..```
and then, once cmake has completed, ```make``` 
can be run from the bin or build directories, with an output in the bin which can be run with ```./boids``` for the main visual project, or timing and testing can be done with the  ```./timing``` and ```./timingMP``` command with usage  
```./timing(MP) <# of boids> <# of timesteps> <# of threads>\n```


## Current State

![Boids Preview](/imgs/boids_preview.gif?raw=true "Boids")


## Project Motivation and References

<a href="https://www.youtube.com/watch?feature=player_embedded&v=4LWmRuB-uNU" target="_blank"><img src="https://img.youtube.com/vi/4LWmRuB-uNU/0.jpg" alt="How Birds Do the Thing - Smarter Every Day 234"/></a>
### How Birds Do the Thing - Smarter Every Day 234


<a href="https://www.youtube.com/watch?feature=player_embedded&v=bqtqltqcQhw" target="_blank"><img src="https://img.youtube.com/vi/bqtqltqcQhw/0.jpg" alt="Coding Adventure: Boids"/></a>
### Coding Adventure: Boids

### [Flocks, Herds, and Schools: A Distributed Behavioral Model](http://www.cs.toronto.edu/~dt/siggraph97-course/cwr87/)

### [Boids Background and Update](http://www.red3d.com/cwr/boids/)

