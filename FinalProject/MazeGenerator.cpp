#include <cstdlib>
#include "MazeGenerator.h"


int **_maze;
bool **_visited;

void MazeGenerator::generateNewMaze(int width, int height)
{
	_width = width;
	_height = height;

	for (int i = 0; i < width; ++i)
	{
		_maze[i] = new int[height];
		_visited[i] = new bool[height];
	}

	for (int i = 0; i < width; i++)
		for(int j = 0; j < height; j++)
		{
			_maze[i][j] = 1;
			_visited[i][j] = false;
		}

	// Set starting point to 0,0 and set visited
	_startPoint.setPoint(0, 0);
	_maze[0][0] = 0;
	_visited[0][0] = true;
	_current = _startPoint;

	// Choose side
	MazePoint next = choosePath(_startPoint);

	// Carve path
	carvePath(_current, next);
	_current = next;
}

void MazeGenerator::carvePath(MazePoint from, MazePoint to)
{
	int dx = to.getX() - from.getX();
	int dy = to.getY() - from.getY();
	
	if (dx == -2) 
		dx = -1;
	else if (dx == 2)
		dx = 1;

	if (dy == -2)
		dy = -1;
	else if (dy == 2)
		dy = 1;

	_maze[from.getX() + dx][from.getY() + dy] = 0;
}

MazePoint MazeGenerator::choosePath(MazePoint point)
{
	MazePoint validPoint[4];
	int counter = 0;

	// West
	if (point.getX() - 2 >= 0 && _maze[point.getX() - 2][point.getY()] == 0)
		validPoint[counter++].setPoint(point.getX() - 2, point.getY());
	
	// East
	if (point.getX() + 2 < _width && _maze[point.getX() + 2][point.getY()] == 0)
		validPoint[counter++].setPoint(point.getX() + 2, point.getY());

	// North
	if (point.getY() - 2 >= 0 && _maze[point.getX()][point.getY() - 2] == 0)
		validPoint[counter++].setPoint(point.getX(), point.getY() - 2);

	// South
	if (point.getY() + 2 < _height && _maze[point.getX()][point.getY() + 2] == 0)
		validPoint[counter++].setPoint(point.getX(), point.getY() + 2);

	while (counter < 4)
		validPoint[counter++].setPoint(-1, -1);

	int num;
	do
	{
		num = rand() % 4;
	} while(validPoint[num].getX() != -1);

	return validPoint[num];
}
