#pragma once

#include "Camera.h"
#include "Maze.h"

class Controller
{
public:
	Controller(void);
	~Controller(void);

	void keyboard(unsigned char key, int x, int y);
	void keyUp(unsigned char key, int x, int y);
	void timerMove(int value, Camera &cam, Maze &maze);
	void mouse(int button, int state, int x, int y);
	void mouseMotion(int x, int y, Camera &cam, Maze &maze);

	int getViewportWidth();
	void setViewportWidth(int width);
	int getViewportHeight();
	void setViewportHeight(int height);

private:
	bool _key[256];
	bool _shiftDown;
	bool _fpsMode;
	int _viewportWidth;
	int _viewportHeight;
	bool _mouseLeftDown;
	bool _mouseRightDown;

	float _rotationSpeed;
	float _translationSpeed;
};
