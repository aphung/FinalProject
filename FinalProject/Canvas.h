#pragma once
#include "Camera.h"
#include "Maze.h"
#include "Hud.h"

class Canvas
{
public:
	Canvas(void);
	~Canvas(void);
	void draw(Camera &cam, Maze &maze, int width, int height);

private:
	void drawGrid(Maze &maze);
	void drawPerimeter(int width, int height);
	void drawCube(int x, int z, int h, int frequency);
	void drawSolidCubeLine(int f_x, int f_z, int t_x, int t_z, int h);
	Hud _hud;
};

