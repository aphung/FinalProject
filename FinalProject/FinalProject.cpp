#include <stdlib.h>
#include <glut.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int WIN_LOC_X = 600;
const int WIN_LOC_Y = 300;

float angle = 0.0f;
float red = 1.0f, green = 1.0f, blue = 1.0f;

void changeSize(int width, int height) {
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

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset Transformations
	glLoadIdentity();

	// Set camera
	gluLookAt(	0.0f, 0.0f, 10.0f,
				0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f);

	glRotatef(angle, 0.0f, 1.0f, 0.0f);

	glColor3f(red, green, blue);
	glBegin(GL_TRIANGLES);
		glVertex3f(-2.0, -2.0, 0.0);
		glVertex3f(2.0, 0.0, 0.0);
		glVertex3f(0.0, 2.0, 0.0);
	glEnd();

	angle += 0.1f;

    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
	// Escape
	if (key == 27)
		exit(0);
	else if (key == 'r') {
		int mod = glutGetModifiers();
		if (mod == GLUT_ACTIVE_ALT)
			red = 0.0;
		else
			red = 1.0;
	}
}

void processSpecialKeys(int key, int x, int y) {
	switch(key) {
	case GLUT_KEY_F1:
		red = 1.0;
		green = 0.0;
		blue = 0.0;
		break;
	case GLUT_KEY_F2:
		red = 0.0;
		green = 1.0;
		blue = 0.0;
		break;
	case GLUT_KEY_F3:
		red = 0.0;
		green = 0.0;
		blue = 1.0;
		break;
	}
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
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	// Keyboard Calls
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);

	// enter GLUT event processing cycle
	glutMainLoop();
	
	return 1;
}