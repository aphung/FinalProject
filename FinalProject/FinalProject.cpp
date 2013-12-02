#include <iostream>
#include <string>
#include <glut.h>
#include <math.h>

#define PI 3.14159

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int WIN_LOC_X = 600;
const int WIN_LOC_Y = 300;

using namespace std;

void renderScene();
void idle();
void changeSize(int width, int height);

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
	glutReshapeFunc(changeSize);
	glutIdleFunc(idle);
	//glutSpecialFunc(pressKey);
	glutIgnoreKeyRepeat(1);
	//glutSpecialUpFunc(releaseKey);

	//glutMouseFunc(mouseButton);
	//glutMotionFunc(mouseMove);

	//createGLUTMenus();

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	glutIgnoreKeyRepeat(1);
	//glutSpecialUpFunc(releaseKey);

	// enter GLUT event processing cycle
	glutMainLoop();
        
	return 1;
}

void renderScene() 
{

}

void idle()
{

}

void changeSize(int width, int height) 
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