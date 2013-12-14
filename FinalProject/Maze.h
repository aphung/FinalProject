#pragma once
#include "MazeGenerator.h"
#include "Direction.h"

class Maze
{
public:
	Maze(void);
	~Maze(void);

	void newMaze(int width, int height); // Create new maze (input size?)
	bool isValidMove(float x, float y, Direction face); // Collision detection

	int getWidth();
	int getHeight();
	int **getMaze();

	void setVisitedAt(int x, int z, int increment);
	int getVisitedAt(int x, int z);
	void markMovement(float x, float z);

private:
	int _sizeWidth, _sizeHeight;
	int** _visited;
	MazeGenerator _mazeGen;

	bool isWithinBoundry(float x, float y);
};

