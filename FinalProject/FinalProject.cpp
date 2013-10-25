#include <stdlib.h>
#include <glut.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int WIN_LOC_X = 600;
const int WIN_LOC_Y = 300;

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
		glVertex3f(-0.5,-0.5,0.0);
		glVertex3f(0.5,0.0,0.0);
		glVertex3f(0.0,0.5,0.0);
	glEnd();

    glutSwapBuffers();
}

int main(int argc, char **argv) {
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(WIN_LOC_X, WIN_LOC_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Final Project - Adam Phung");

	// register callbacks
	glutDisplayFunc(renderScene);

	// enter GLUT event processing cycle
	glutMainLoop();
	
	return 1;
}