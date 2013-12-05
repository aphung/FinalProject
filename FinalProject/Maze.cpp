#include <stdio.h>
#include <math.h>

#include "Maze.h"

int** _maze;

Maze::Maze(void)
{
}


Maze::~Maze(void)
{
}

void Maze::newMaze(int width, int height)
{
	_maze = new int*[width];

	for(int i = 0; i < width; ++i)
		_maze[i] = new int[height];
}

// TODO: rename this to yes/no statement
bool Maze::travelMaze(float x, float y)
{
	// TODO: scope these to class
	int width = 0;
	int height = 0;

	// Check boundries first
	if (x < 0 || x > width)
		return false;
	if (y < 0 || y > height)
		return false;

	// Check maze array
}