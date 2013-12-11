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
	_mazeGen.generateNewMaze(width, height);
	_maze = _mazeGen.getMaze();

	_sizeWidth = width;
	_sizeHeight = height;
}

bool Maze::isValidMove(float x, float y)
{
	// Check boundries
	if (x < -0.25 || x > _sizeWidth - 0.75)
		return false;

	if (y < -0.25 || y > _sizeHeight - 0.75)
		return false;

	// Check maze array
	//x -= 0.25;
	//y -= 0.25;
	int check_x = int(x + 0.5);
	int check_y = int(y + 0.5);

	//// Check upper bound
	//if (check_x >= _sizeWidth || check_y >= _sizeHeight)
	//	return false;

	if (_maze[check_x][check_y] > 0)
		return false;

	// Valid move
	return true;
}

int Maze::getWidth() { return _sizeWidth; }
int Maze::getHeight() { return _sizeHeight; }
int **Maze::getMaze() { return _maze; }
