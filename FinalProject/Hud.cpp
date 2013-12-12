#include <stdio.h>
#include <iostream>
#include <math.h>
#include <glut.h>
#include <string.h>

#include "Hud.h"

using namespace std;

Hud::Hud(void)
{
}


Hud::~Hud(void)
{
}

void Hud::drawHud(Camera &cam, int width, int height)
{
	float x, z, y;

	glPushMatrix();
	glLoadIdentity();
	setOrthographicProjection(width, height);

	drawCrosshair(width/2, height/2, 10);

	cam.GetPos(x, y, z);
	drawLocation(x, y, z);

	cam.GetDirectionVector(x, y, z);
	drawLookAt(x, y, z);

	glPopMatrix();
	restorePerspectiveProjection();
}

void Hud::setOrthographicProjection(int width, int height) 
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    gluOrtho2D(0, width, height, 0);

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
	{
		glutBitmapCharacter(font, *c);
	}
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

void Hud::drawLookAt(float x, float y, float z)
{
	char dir[5];
	switch (getDirection(x * 100, z * 100))
	{
	case Direction::NORTH:
		sprintf(dir, "N");
		break;
	case Direction::NORTHEAST:
		sprintf(dir, "NE");
		break;
	case Direction::EAST:
		sprintf(dir, "E");
		break;
	case Direction::SOUTHEAST:
		sprintf(dir, "SE");
		break;
	case Direction::SOUTH:
		sprintf(dir, "S");
		break;
	case Direction::SOUTHWEST:
		sprintf(dir, "SW");
		break;
	case Direction::WEST:
		sprintf(dir, "W");
		break;
	case Direction::NORTHWEST:
		sprintf(dir, "NW");
		break;
	}

	char loc[50];
	sprintf(loc, "%4.0f %4.0f %4.0f", x*100, y*100, z*100);

	glColor3f(0.0f, 1.0f, 1.0f);
	renderBitmapString(10.0, 35.0, GLUT_BITMAP_HELVETICA_18, loc);
	renderBitmapString(200.0, 35.0, GLUT_BITMAP_HELVETICA_18, dir);
}

Direction Hud::getDirection(float x, float z)
{
	Direction facing = Direction::NORTH;

	if (x > -35)
	{
		if (x < 35) // W or E
		{
			if (z > 0) // E
				facing = Direction::EAST;
			else // W
				facing = Direction::WEST;
		}
		else // NW, N or NE
		{
			if (x >= 85) // N
				facing = Direction::NORTH;
			else if (z < 0) // NW
				facing = Direction::NORTHWEST;
			else // NE
				facing = Direction::NORTHEAST;

		}
	}
	else // x <= -35 SW, S or SE
	{
		if (x <= -85) // S
			facing = Direction::SOUTH;
		else if (z < 0) // SW
			facing = Direction::SOUTHWEST;
		else // SE
			facing = Direction::SOUTHEAST;
	}

	return facing;
}
