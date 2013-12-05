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

// TODO: rename this to yes/no statement
bool Maze::travelMaze(float x, float y)
{
	int startWidth = 0 - (_sizeWidth/2);
	int startEnd = 0 - (_sizeHeight/2);

	// Check boundries first
	if (x < startWidth || x > _sizeWidth/2)
		return false;
	if (y < startEnd || y > _sizeHeight/2)
		return false;

	// Check maze array

	// return
	return true; // valid move
}