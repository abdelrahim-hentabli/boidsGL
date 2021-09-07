#ifndef SDL_FUNC_H
#define SDL_FUNC_H

#include <GL/glut.h>
#include "boids.h"
#include "vec.h"

#include<math.h>
#define pi 3.142857

void myInit (void)
{
    // making background color black as first
    // 3 arguments all are 0.0
    glClearColor(0.0, 0.0, 0.0, 1.0);
     
    // making picture color green (in RGB mode), as middle argument is 1.0
    glColor3f(0.0, 1.0, 0.0);
     
    // breadth of picture boundary is 1 pixel
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
     
    // setting window dimension in X- and Y- direction
    gluOrtho2D(-780, 780, -420, 420);
}
 
void display (void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    float x, y, i;
     
    // iterate y up to 2*pi, i.e., 360 degree
    // with small increment in angle as
    // glVertex2i just draws a point on specified co-ordinate
    while(true){
        for ( i = 0; i < (2 * pi); i += 0.001)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glBegin(GL_POINTS);
            // let 200 is radius of circle and as,
            // circle is defined as x=r*cos(i) and y=r*sin(i)
            x = 200 * cos(i);
            y = 200 * sin(i);
         
            glVertex2i(x, y);
        }
        glEnd();
        glFlush();
    }
    glEnd();
    glFlush();
}

#endif //SDL_FUNC_H