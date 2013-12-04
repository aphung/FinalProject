#pragma once

class Controller
{
public:
	Controller(void);
	~Controller(void);

	void keyboard(unsigned char key, int x, int y);
	void keyUp(unsigned char key, int x, int y);

private:
	bool _key[256];
	bool _shiftDown;
	bool _fpsMode;
	int _viewportWidth;
	int _viewportHeight;
	bool _mouseLeftDown;
	bool _mouseRightDown;
};

