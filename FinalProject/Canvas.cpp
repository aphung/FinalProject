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

	// Draw start and end points
	char str[] = "Start";
	drawMarker(-1, -1, 10, 23.0/255.0f, 1.0f, 100.0/255.0f, str);
	drawMarker(maze.getWidth(), maze.getHeight(), 10, 235.0/255.0f, 40.0/255.0f, 92.0/255.0f, str);

	// location text
	_hud.drawHud(cam, width, height);

    glutSwapBuffers(); //swap the buffers
}

void Canvas::drawPerimeter(int w, int h)
{
	drawSolidCubeLine(-1, -1, -1, h, 1);
	drawSolidCubeLine(-1, -1, w, -1, 1);
	drawSolidCubeLine(-1, h, w, h, 1);
	drawSolidCubeLine(w, -1, w, h, 1);
}

// draw line cubes from f to t
void Canvas::drawSolidCubeLine(int f_x, int f_z, int t_x, int t_z, int h)
{
	int incr;
	if (f_x == t_x)
		incr = t_z;
	else
		incr = t_x;

	for (int i = -1; i <= incr; i++)
	{
		glColor3f(0, 1, 0);
		glPushMatrix();

		if (f_x == t_x)
			glTranslatef(f_x, h, i);
		else
			glTranslatef(i, h, f_z);
		
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
				drawCube(i, j, grid[i][j], maze.getVisitedAt(i, j));
		}
	}

    glPopMatrix();
}

void Canvas::drawCube(int x, int z, int h, int freq)
{
	if (h > 0)
	{
		for(int i = 0; i <= h; i++)
		{
			glColor3f(1, 1, 0);
			glPushMatrix();
			glTranslatef(x, i, z);
			glutSolidCube(1.0);
			glPopMatrix();
		}
	} 
	else
	{
		switch(freq)
		{
		case 0:
			glColor3f(0.0, 0.0, 1.0);
			break;
		case 1:
			glColor3f(0.0, 0.5, 1.0);
			break;
		case 2:
			glColor3f(0.0, 0.75, 1.0);
			break;
		default:
			glColor3f(0.0, 1.0, 1.0);
			break;
		}
		glPushMatrix();
		glTranslatef(x, h, z);
		glutSolidCube(1.0);
		glPopMatrix();
	}
}

void Canvas::drawMarker(int x, int z, int h, float r, float g, float b, char text[])
{

	for (int i = 2; i < h+2; i++)
	{
		glColor3f(r, g, b);
		glPushMatrix();
		glTranslatef(x, i, z);
		glutSolidCube(1.0);
		glPopMatrix();
	}
}
