#ifndef CONSTANTS_H
#define CONSTANTS_H

struct boid;

const float PI = 3.14159f;

boid* the_boids;
const int BOIDS_COUNT = 100;

int threads = 8;

//angle from forward that a boid can see, actual vision size = 2 * BOID_VIEW_ANGLE
const float BOID_VIEW_ANGLE_DEGREES = 120;
const float BOID_VIEW_ANGLE_RADIANS = BOID_VIEW_ANGLE_DEGREES * PI / 180.0;

const float BOID_VIEW_DIST = 2;
const float BOID_VIEW_DIST_SQR = BOID_VIEW_DIST * BOID_VIEW_DIST;

const float BOID_AVOID_DIST = 2;
const float BOID_AVOID_DIST_SQR = BOID_AVOID_DIST * BOID_AVOID_DIST;

const float OBS_AVOID_DIST = 3;

const float ALIGNMENT_WEIGHT = 1;
const float COHESION_WEIGHT = 1;
const float SEPERATION_WEIGHT = 1;
const float OBS_AVOID_WEIGHT = 0;

const float WORLD_X_MIN = -40;
const float WORLD_X_MAX = 40;

const float WORLD_Y_MIN = -22.5;
const float WORLD_Y_MAX = 22.5;


const int SCREEN_WIDTH = 768;
const int SCREEN_HEIGHT = 480;

const float BOID_DRAW_ANGLE_DEGREES = 125;
const float BOID_DRAW_ANGLE_RADIANS = BOID_DRAW_ANGLE_DEGREES * PI / 180.0;



#endif //CONSTANTS_H