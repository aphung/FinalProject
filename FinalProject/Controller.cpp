#include <stdio.h>
#include <math.h>
#include <glut.h>
#include "Controller.h"

Controller::Controller(void)
{
	for (int i = 0; i < 256; i++)
		_key[i] = false;

}


Controller::~Controller(void)
{
}

void Controller::keyboard(unsigned char key, int x, int y)
{
	if (key == 27) // Escape key
		exit(0);

	_key[key] = true;
}

void Controller::keyUp(unsigned char key, int x, int y)
{
	_key[key] = false;
}