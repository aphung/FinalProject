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

	for(int i = 0; i < width; i++)
		for(int j = 0; j < height; j++)
			_maze[i][j] = 0;

	_sizeWidth = width;
	_sizeHeight = height;

	_maze[20][20] = 2; // test location
	_maze[20][19] = 1;
}

bool Maze::isValidMove(float x, float y)
{
	// Check boundries
	if (x < 0 || x > _sizeWidth)
		return false;

	if (y < 0 || y > _sizeHeight)
		return false;

	// Check maze array
	int check_x = int(x + 0.5);
	int check_y = int(y + 0.5);

	if (_maze[check_x][check_y] > 0)
		return false;

	// Valid move
	return true;
}

int Maze::getWidth() { return _sizeWidth; }
int Maze::getHeight() { return _sizeHeight; }
int **Maze::getMaze() { return _maze; }
