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
    glClearColor(0.0, 0.0, 0.0, 1.0); //clear the screen to black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
    glLoadIdentity();

	cam.Refresh();

    glColor3f(0, 1, 0);

    glutWireTeapot(0.5);
    drawGrid(maze);

	glBegin(GL_LINES);
	glVertex3f(5.0, 1.0, 5.0);
	glutWireTeapot(0.5);
	glEnd();

	// location text
	_hud.drawHud(cam, width, height);

    glutSwapBuffers(); //swap the buffers
}

// Temp grid
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

	//for(int i=0; i <= maze.getWidth(); i++) {
 //       glBegin(GL_LINES);
 //       glVertex3f(i, 0, 0);
 //       glVertex3f(i, 0, maze.getHeight());
 //       glEnd();
 //   }

	//for(int i=0; i <= maze.getHeight(); i++) {
 //       glBegin(GL_LINES);
 //       glVertex3f(0, 0, i);
 //       glVertex3f(maze.getWidth(), 0, i);
 //       glEnd();
 //   }

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
			glutWireCube(1);
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



	//if (h > 0)
	//{
	//	glBegin(GL_LINES);
	//	glVertex3f(x, h, z);
	//	glVertex3f(x, h - 1, z);
	//	glEnd();

	//	glBegin(GL_LINES);
	//	glVertex3f(x + 1, h, z);
	//	glVertex3f(x + 1, h - 1, z);
	//	glEnd();

	//	glBegin(GL_LINES);
	//	glVertex3f(x + 1, h, z + 1);
	//	glVertex3f(x + 1, h - 1, z + 1);
	//	glEnd();

	//	glBegin(GL_LINES);
	//	glVertex3f(x, h, z + 1);
	//	glVertex3f(x, h - 1, z + 1);
	//	glEnd();
	//}
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