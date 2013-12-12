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

void Canvas::draw(Camera &cam, Maze &maze, int width, int height)
{
    glClearColor(0.196, 0.6, 0.8, 1.0); // Background: sky blue
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
    glLoadIdentity();

	cam.Refresh();

    glColor3f(0, 1, 0);

	// Draw Maze and Floor
    drawGrid(maze);

	// Draw Perimieter
	drawPerimeter(maze.getWidth(), maze.getHeight());

	// location text
	_hud.drawHud(cam, width, height);

    glutSwapBuffers(); //swap the buffers
}

void Canvas::drawPerimeter(int w, int h)
{
	for (int i = 0; i < w; i++)
	{
		glColor3f(0, 1, 0);
		glPushMatrix();
		glTranslatef(-1, 1, i);
		glutSolidCube(1);
		glPopMatrix();
	}

	for (int i = 0; i < w; i++)
	{
		glColor3f(0, 1, 0);
		glPushMatrix();
		glTranslatef(h, 1, i);
		glutSolidCube(1);
		glPopMatrix();
	}

	for (int i = 0; i < h; i++)
	{
		glColor3f(0, 1, 0);
		glPushMatrix();
		glTranslatef(i, 1, -1);
		glutSolidCube(1);
		glPopMatrix();
	}

	for (int i = 0; i < h; i++)
	{
		glColor3f(0, 1, 0);
		glPushMatrix();
		glTranslatef(i, 1, w);
		glutSolidCube(1);
		glPopMatrix();
	}
}

// grid and floor
void Canvas::drawGrid(Maze &maze)
{
    glPushMatrix();
    glColor3f(1,1,1);

	int **grid = maze.getMaze();

	for(int i = 0; i < maze.getWidth(); i++)
	{
		for(int j = 0; j < maze.getHeight(); j++)
		{
			for(int h = 0; h <= grid[i][j]; h++)
				drawCube(i, j, grid[i][j]);
		}
	}

    glPopMatrix();
}

void Canvas::drawCube(int x, int z, int h)
{
	if (h > 0)
	{
		for(int i = 1; i <= h; i++)
		{
			glColor3f(1, 1, 0);
			glPushMatrix();
			glTranslatef(x, i, z);
			glutSolidCube(0.5);
			glPopMatrix();
		}
	} 
	else
	{
		glColor3f(0.0, 0.0, 1.0);
		glPushMatrix();
		glTranslatef(x, h, z);
		glutSolidCube(1);
		glPopMatrix();
	}
}

void Canvas::drawSquare(int x, int z, int h)
{
	// Left
	glBegin(GL_LINES);
	glVertex3f(x, h, z);
	glVertex3f(x + 1, h, z);
	glEnd();

	// Top
	glBegin(GL_LINES);
	glVertex3f(x + 1, h, z);
	glVertex3f(x + 1, h, z + 1);
	glEnd();

	// Right
	glBegin(GL_LINES);
	glVertex3f(x + 1, h, z + 1);
	glVertex3f(x, h, z + 1);
	glEnd();

	// Bottom
	glBegin(GL_LINES);
	glVertex3f(x, h, z + 1);
	glVertex3f(x, h, z);
	glEnd();
}