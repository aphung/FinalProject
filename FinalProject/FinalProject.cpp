#include <stdio.h>
#include <iostream>
#include <string>
#include <glut.h>
#include <math.h>

#include "Camera.h"
#include "Controller.h"
#include "Canvas.h"

#define PI 3.14159265358979323846

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int WIN_LOC_X = 600;
const int WIN_LOC_Y = 300;

using namespace std;

// Callback method declarations
void renderScene();
void idle();
void timer(int value);
void reshapeScene(int width, int height);
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);

// temp methods
void display(void);

// Class variables
Camera _camera;
Controller _controller;
Canvas _canvas;
Maze _maze;

int main (int argc, char **argv)
{
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(WIN_LOC_X, WIN_LOC_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Final Project - Adam Phung");

	// Lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	GLfloat lightpos[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light[] = {0.5, 0.5, 0.0 }; // Light Color
	GLfloat cyan[] = {0.f, .8f, .8f, 1.f};

	glShadeModel (GL_SMOOTH);

	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glEnable(GL_COLOR_MATERIAL); // color material

	glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(reshapeScene);
	glutIdleFunc(idle);

	// register input callbacks
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
    glutPassiveMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
	glutIgnoreKeyRepeat(1);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// New Maze
	_maze.newMaze(25, 25);

	// enter GLUT event processing cycle
	glutTimerFunc(1, timer, 0);
	glutMainLoop();
        
	return 1;
}

void renderScene() 
{
	display();
}

void idle()
{
	display();
}

// Draw
void display(void)
{
	_canvas.draw(_camera, _maze, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void timer(int value)
{
	_controller.timerMove(value, _camera, _maze);
    glutTimerFunc(1, timer, 0);
}

void reshapeScene(int width, int height) 
{
	_controller.setViewportWidth(width);
	_controller.setViewportHeight(height);

    glViewport(0, 0, (GLsizei)width, (GLsizei)height); //set the viewport to the current window specifications
    glMatrixMode(GL_PROJECTION); //set the matrix to projection

    glLoadIdentity();
    gluPerspective(60, (GLfloat)width / (GLfloat)height, 0.1 , 100.0); //set the perspective (angle of sight, width, height, ,depth)
    glMatrixMode(GL_MODELVIEW); //set the matrix back to model
}

void mouse(int button, int state, int x, int y)
{
	_controller.mouse(button, state, x, y);
}

void mouseMotion(int x, int y)
{
	_controller.mouseMotion(x, y, _camera, _maze);
}

void keyboard(unsigned char key, int x, int y)
{
	_controller.keyboard(key, x, y);
}

void keyboardUp(unsigned char key, int x, int y)
{
	_controller.keyUp(key, x, y);
}
