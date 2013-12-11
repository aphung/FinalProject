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
	void drawCube(int x, int z, int h);
	void drawSquare(int x, int z, int h);
	Hud _hud;
};

