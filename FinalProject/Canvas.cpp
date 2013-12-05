#include <stdio.h>
#include <math.h>
#include <glut.h>

#include "Canvas.h"

Canvas::Canvas(void)
{
}


Canvas::~Canvas(void)
{
}

void Canvas::draw(Camera &cam, int width, int height)
{
    glClearColor(0.0, 0.0, 0.0, 1.0); //clear the screen to black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
    glLoadIdentity();

	cam.Refresh();

    glColor3f(0, 1, 0);

    glutWireTeapot(0.5);
    Grid();

	glBegin(GL_LINES);
	glVertex3f(5.0, 1.0, 5.0);
	glutWireTeapot(0.5);
	glEnd();

	// location text
	_hud.drawHud(cam, width, height);


    glutSwapBuffers(); //swap the buffers
}

// Temp grid
void Canvas::Grid(void)
{
    glPushMatrix();
    glColor3f(1,1,1);

    for(int i=-50; i < 50; i++) {
        glBegin(GL_LINES);
        glVertex3f(i, 0, -50);
        glVertex3f(i, 0, 50);
        glEnd();
    }

    for(int i=-50; i < 50; i++) {
        glBegin(GL_LINES);
        glVertex3f(-50, 0, i);
        glVertex3f(50, 0, i);
        glEnd();
    }

    glPopMatrix();
}