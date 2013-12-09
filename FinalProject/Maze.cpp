#include <stdio.h>
#include <math.h>

#include "Maze.h"

int** _maze;

Maze::Maze(void)
{
	_sizeWidth = 100; // Default size
	_sizeHeight = 100;
}


Maze::~Maze(void)
{
}

void Maze::newMaze(int width, int height)
{
	_maze = new int*[width];

	for(int i = 0; i < width; ++i)
		_maze[i] = new int[height];

	_sizeWidth = width;
	_sizeHeight = height;
}

bool Maze::isValidMove(float x, float y)
{
	// Check boundries
	if (x < 0 || x > _sizeWidth)
		return false;

	if (y < 0 || y > _sizeHeight)
		return false;

	// Check maze array

	// Valid move
	return true;
}

int Maze::getWidth() { return _sizeWidth; }
int Maze::getHeight() { return _getHeight; }