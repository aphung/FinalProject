#pragma once
#include "Camera.h"

class Hud
{
public:
	Hud(void);
	~Hud(void);

	void drawHud(Camera &cam, int width, int height);

private:
	void setOrthographicProjection(int width, int height);
	void restorePerspectiveProjection();
	void renderBitmapString(float x, float y, void *font, const char *string);
	void drawLocation(float x, float y, float z);
	void drawCrosshair(float x, float y, int size);
};

