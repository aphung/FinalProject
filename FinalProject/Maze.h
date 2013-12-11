#pragma once
#include "MazeGenerator.h"

class Maze
{
public:
	Maze(void);
	~Maze(void);

	void newMaze(int width, int height); // Create new maze (input size?)
	bool isValidMove(float x, float y); // Collision detection

	int getWidth();
	int getHeight();
	int **getMaze();

private:
	int _sizeWidth, _sizeHeight;
	MazeGenerator _mazeGen;

	bool isWithinBoundry(float x, float y);
};

