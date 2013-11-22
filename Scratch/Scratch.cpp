#include <stdlib.h>
#include <glut.h>
#include <math.h>
#include <iostream>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int WIN_LOC_X = 600;
const int WIN_LOC_Y = 300;

float angle = 0.0f;
float lx = 0.0f, lz = -1.0f;
float x = 0.0f, z = 5.0f;

float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;
int frame=0,time,timebase=0;

float red = 1.0f, green = 0.5f, blue = 0.5f;

char str[50], loc[50];

#define RED 1
#define GREEN 2
#define BLUE 3
#define ORANGE 4

void setOrthographicProjection() {

        // switch to projection mode
        glMatrixMode(GL_PROJECTION);

        // save previous matrix which contains the
        //settings for the perspective projection
        glPushMatrix();

        // reset matrix
        glLoadIdentity();

        // set a 2D orthographic projection
        gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

        // switch back to modelview mode
        glMatrixMode(GL_MODELVIEW);
}

void restorePerspectiveProjection() {

        glMatrixMode(GL_PROJECTION);
        // restore previous projection matrix
        glPopMatrix();

        // get back to modelview mode
        glMatrixMode(GL_MODELVIEW);
}

void renderBitmapString(float x, float y, void *font, const char *string) {
  const char *c;
  glRasterPos2f(x, y);
  for (c = string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }
}

void processMenuEvents(int option) {

        switch (option) {
                case RED :
                        red = 1.0f;
                        green = 0.0f;
                        blue = 0.0f; break;
                case GREEN :
                        red = 0.0f;
                        green = 1.0f;
                        blue = 0.0f; break;
                case BLUE :
                        red = 0.0f;
                        green = 0.0f;
                        blue = 1.0f; break;
                case ORANGE :
                        red = 1.0f;
                        green = 0.5f;
                        blue = 0.5f; break;
        }
}

void createGLUTMenus() {
        int menu;

        // create the menu and
        // tell glut that "processMenuEvents" will
        // handle the events
        menu = glutCreateMenu(processMenuEvents);

        //add entries to our menu
        glutAddMenuEntry("Red",RED);
        glutAddMenuEntry("Blue",BLUE);
        glutAddMenuEntry("Green",GREEN);
        glutAddMenuEntry("Orange",ORANGE);

        // attach the menu to the right button
        glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void drawSnowMan() {
        glColor3f(1.0f, 1.0f, 1.0f);

        // Draw Body
        glTranslatef(0.0f ,0.75f, 0.0f);
        glutSolidSphere(0.75f,20,20);

        // Draw Head
        glTranslatef(0.0f, 1.0f, 0.0f);
        glutSolidSphere(0.25f,20,20);

        // Draw Eyes
        glPushMatrix();
        glColor3f(0.0f,0.0f,0.0f);
        glTranslatef(0.05f, 0.10f, 0.18f);
        glutSolidSphere(0.05f,10,10);
        glTranslatef(-0.1f, 0.0f, 0.0f);
        glutSolidSphere(0.05f,10,10);
        glPopMatrix();

        // Draw Nose
        glColor3f(red, green , blue);
        glRotatef(0.0f,1.0f, 0.0f, 0.0f);
        glutSolidCone(0.08f,0.5f,10,2);
}

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

void computePos(float deltaMove) {
        x += deltaMove * lx * 0.1f;
        z += deltaMove * lz * 0.1f;
}

void computeDir(float deltaAngle) {
        angle += deltaAngle;
        lx = sin(angle);
        lz = -cos(angle);
}

void renderScene(void) {

        if (deltaMove)
                computePos(deltaMove);
        if (deltaAngle)
                computeDir(deltaAngle);

        // Clear Color and Depth Buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Reset transformations
        glLoadIdentity();

        // Set the camera
        gluLookAt(        x, 1.0f, z,
                        x+lx, 1.0f, z+lz,
                        0.0f, 1.0f, 0.0f);

    // Draw ground
        glColor3f(0.9f, 0.9f, 0.9f);
        glBegin(GL_QUADS);
                glVertex3f(-100.0f, 0.0f, -100.0f);
                glVertex3f(-100.0f, 0.0f, 100.0f);
                glVertex3f( 100.0f, 0.0f, 100.0f);
                glVertex3f( 100.0f, 0.0f, -100.0f);
        glEnd();

    // Draw 36 SnowMen
        for(int i = -3; i < 3; i++) {
                for(int j=-3; j < 3; j++) {
                        glPushMatrix();
                        glTranslatef(i*10.0,0,j * 10.0);
                        drawSnowMan();
                        glPopMatrix();
                }
        }

        
        // FPS and Location Text
        frame++;
        time=glutGet(GLUT_ELAPSED_TIME);
        if (time - timebase > 1000) {
                sprintf(str,"FPS:%4.2f",
                        frame*1000.0/(time-timebase));
                timebase = time;
                frame = 0;
        }

        sprintf(loc, "Location: %4.2f, %4.2f", x, z);
        glColor3f(0.0f,1.0f,1.0f);

        glPushMatrix();
        glLoadIdentity();
        setOrthographicProjection();
        renderBitmapString(420.0, 35.0, GLUT_BITMAP_HELVETICA_18, loc);
        renderBitmapString(30,35,GLUT_BITMAP_HELVETICA_18,str);
        glPopMatrix();
        restorePerspectiveProjection();

        glutSwapBuffers();
}

void mouseButton(int button, int state, int x, int y) {
        // only start motion if the left button is pressed
        if (button == GLUT_LEFT_BUTTON) {
                // when the button is released
                if (state == GLUT_UP) {
                        angle += deltaAngle;
                        xOrigin = -1;
                }
                else {// state = GLUT_DOWN
                        xOrigin = x;
                }
        }
}

void mouseMove(int x, int y) {
        // this will only be true when the left button is down
        if (xOrigin >= 0) {
                // update deltaAngle
                deltaAngle = (x - xOrigin) * 0.001f;

                // update camera's direction
                lx = sin(angle + deltaAngle);
                lz = -cos(angle + deltaAngle);
        }
}

void pressKey(int key, int xx, int yy) {

        switch (key) {
                case GLUT_KEY_LEFT:
                        deltaAngle = -0.01f;
                        break;
                case GLUT_KEY_RIGHT:
                        deltaAngle = 0.01f;
                        break;
                case GLUT_KEY_UP:
                        deltaMove = 0.5f;
                        break;
                case GLUT_KEY_DOWN:
                        deltaMove = -0.5f;
                        break;
        }
}

void releaseKey(int key, int x, int y) {

        switch (key) {
                case GLUT_KEY_LEFT:
                case GLUT_KEY_RIGHT:
                        deltaAngle = 0.0f;
                        break;
                case GLUT_KEY_UP:
                case GLUT_KEY_DOWN:
                        deltaMove = 0;
                        break;
        }
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
        float fraction = 0.5f;

        switch (key) {
                case GLUT_KEY_LEFT :
                        angle -= 0.01f;
                        lx = sin(angle);
                        lz = -cos(angle);
                        break;
                case GLUT_KEY_RIGHT :
                        angle += 0.01f;
                        lx = sin(angle);
                        lz = -cos(angle);
                        break;
                case GLUT_KEY_UP :
                        x += lx * fraction;
                        z += lz * fraction;
                        break;
                case GLUT_KEY_DOWN :
                        x -= lx * fraction;
                        z -= lz * fraction;
                        break;
        }
}

int main(int argc, char **argv) {
        // init GLUT and create window
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
        glutInitWindowPosition(WIN_LOC_X, WIN_LOC_Y);
        glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        glutCreateWindow("Final Project - Adam Phung");

        // register callbacks
        glutDisplayFunc(renderScene);
        glutReshapeFunc(changeSize);
        glutIdleFunc(renderScene);
        glutSpecialFunc(pressKey);
        glutIgnoreKeyRepeat(1);
        glutSpecialUpFunc(releaseKey);

        glutMouseFunc(mouseButton);
        glutMotionFunc(mouseMove);

        createGLUTMenus();

        // OpenGL init
        glEnable(GL_DEPTH_TEST);

        glutIgnoreKeyRepeat(1);
        glutSpecialUpFunc(releaseKey);

        // enter GLUT event processing cycle
        glutMainLoop();
        
        return 1;
}