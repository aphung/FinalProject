#include <stdio.h>
#include <math.h>
#include <glut.h>
#include "Controller.h"

#define PI 3.14159265358979323846

Controller::Controller(void)
{
	for (int i = 0; i < 256; i++)
		_key[i] = false;

	_shiftDown = false;
	_fpsMode = false;
	_viewportWidth= 0;
	_viewportHeight = 0;
	_mouseLeftDown = false;
	_mouseRightDown = false;

	_rotationSpeed = PI / 180 * 0.2;
	_translationSpeed = 0.05;
}


Controller::~Controller(void)
{
}

void Controller::keyboard(unsigned char key, int x, int y)
{
	if (key == 27) // Escape key
		exit(0);

    if(key == ' ') {
        _fpsMode = !_fpsMode;

        if(_fpsMode) {
            glutSetCursor(GLUT_CURSOR_NONE);
            glutWarpPointer(_viewportWidth/2, _viewportHeight/2);
        }
        else {
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        }
    }

    if(glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
        _shiftDown = true;
    }
    else {
        _shiftDown = false;
    }

	_key[key] = true;
}

void Controller::keyUp(unsigned char key, int x, int y)
{
	_key[key] = false;
}

void Controller::timerMove(int value, Camera &cam)
{
    if(_fpsMode) 
	{
        if(_key['w'] || _key['W']) 
		{
            cam.Move(_translationSpeed);
        }
        if(_key['s'] || _key['S']) 
		{
            cam.Move(-_translationSpeed);
        }
        if(_key['a'] || _key['A']) 
		{
            cam.Strafe(_translationSpeed);
        }
        if(_key['d'] || _key['D']) 
		{
            cam.Strafe(-_translationSpeed);
        }
        if(_mouseLeftDown) 
		{
            cam.Fly(-_translationSpeed);
        }
        if(_mouseRightDown) 
		{
            cam.Fly(_translationSpeed);
        }
    }
}


// Mouse Functions

void Controller::mouse(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN) {
        if(button == GLUT_LEFT_BUTTON) {
            _mouseLeftDown = true;
        }
        else if(button == GLUT_RIGHT_BUTTON) {
            _mouseRightDown = true;
        }
    }
    else if(state == GLUT_UP) {
        if(button == GLUT_LEFT_BUTTON) {
            _mouseLeftDown = false;
        }
        else if(button == GLUT_RIGHT_BUTTON) {
            _mouseRightDown = false;
        }
    }
}

void Controller::mouseMotion(int x, int y, Camera &cam)
{
    // This variable is hack to stop glutWarpPointer from triggering an event callback to Mouse(...)
    // This avoids it being called recursively and hanging up the event loop
    static bool just_warped = false;

    if(just_warped) {
        just_warped = false;
        return;
    }

    if(_fpsMode) {
        int dx = x - _viewportWidth/2;
        int dy = y - _viewportHeight/2;

        if(dx) {
            cam.RotateYaw(_rotationSpeed * dx);
        }

        if(dy) {
			cam.RotatePitch(-_rotationSpeed * dy);
        }

        glutWarpPointer(_viewportWidth/2, _viewportHeight/2);

        just_warped = true;
    }
}

int Controller::getViewportWidth() { return _viewportWidth; }
void Controller::setViewportWidth(int width) { _viewportWidth = width; }
int Controller::getViewportHeight() { return _viewportHeight; }
void Controller::setViewportHeight(int height) { _viewportHeight = height; }
