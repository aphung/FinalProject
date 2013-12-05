#pragma once
class Hud
{
public:
	Hud(void);
	~Hud(void);

	void setOrthographicProjection(int width, int height);
	void restorePerspectiveProjection();
	void renderBitmapString(float x, float y, void *font, const char *string);
};

