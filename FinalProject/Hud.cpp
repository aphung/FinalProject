#include <stdio.h>
#include <math.h>
#include <glut.h>

#include "Hud.h"

Hud::Hud(void)
{
}


Hud::~Hud(void)
{
}

void Hud::setOrthographicProjection(int width, int height) 
{
    // switch to projection mode
    glMatrixMode(GL_PROJECTION);

    // save previous matrix which contains the
    //settings for the perspective projection
    glPushMatrix();

    // reset matrix
    glLoadIdentity();

    // set a 2D orthographic projection
    gluOrtho2D(0, width, height, 0);

    // switch back to modelview mode
    glMatrixMode(GL_MODELVIEW);
}

void Hud::restorePerspectiveProjection() 
{
	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void Hud::renderBitmapString(float x, float y, void *font, const char *string) 
{
	const char *c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) 
		glutBitmapCharacter(font, *c);
}