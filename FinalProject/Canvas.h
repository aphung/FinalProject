#pragma once
#include "Camera.h"
#include "Hud.h"

class Canvas
{
public:
	Canvas(void);
	~Canvas(void);
	void draw(Camera &cam, int width, int height);

private:
	void Grid();
	Hud _hud;
};

