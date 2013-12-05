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

void Hud::drawHud(Camera &cam, int width, int height)
{
	float x, z, y;
	cam.GetPos(x, y, z);

	glPushMatrix();
	glLoadIdentity();
	setOrthographicProjection(width, height);

	drawCrosshair(width/2, height/2, 10);
	drawLocation(x, y, z);

	glPopMatrix();
	restorePerspectiveProjection();
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

// draw location relative to 2D plane
void Hud::drawLocation(float x, float y, float z)
{
	char loc[50];
	sprintf(loc, "%4.2f, %4.2f, %4.2f", x, y, z);
	glColor3f(0.0f,1.0f,1.0f);
	renderBitmapString(450.0, 35.0, GLUT_BITMAP_HELVETICA_18, loc);
}

void Hud::drawCrosshair(float x, float y, int size)
{
    glColor3f(1, 0, 0);

    glBegin(GL_LINES);
    glVertex2f(x - size, y);
    glVertex2f(x + size, y);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(x, y - size);
    glVertex2f(x, y + size);
    glEnd();
}