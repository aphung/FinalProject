#include <iostream>
#include <string>
#include <glut.h>
#include <math.h>

#include "Controller.h"

#define PI 3.14159265359

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

// Main variables
Controller _controller;

int main (int argc, char **argv)
{
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(WIN_LOC_X, WIN_LOC_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Final Project - Adam Phung");

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

	// enter GLUT event processing cycle
	glutTimerFunc(1, timer, 0);
	glutMainLoop();
        
	return 1;
}

void renderScene() 
{

}

void idle()
{

}

void timer(int value)
{

}

void reshapeScene(int width, int height) 
{
	if (height == 0)
		height = 1;
	float ratio = width * 1.0 / height;

	// Use Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set viewport to the entire window
	glViewport(0, 0, width, height);

	// Set correct perspective
	gluPerspective(45, ratio, 1, 100);

	// Get back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y)
{

}

void mouseMotion(int x, int y)
{

}

void keyboard(unsigned char key, int x, int y)
{
	_controller.keyboard(key, x, y);
}

void keyboardUp(unsigned char key, int x, int y)
{
	_controller.keyUp(key, x, y);
}