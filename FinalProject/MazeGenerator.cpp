#include <cstdlib>
#include <time.h>

#include "MazeGenerator.h"
#include "MazePointStack.h"

MazePointStack stack;

MazeGenerator::MazeGenerator(void)
{
	srand(time(NULL));
}

MazeGenerator::~MazeGenerator(void)
{

}

int** MazeGenerator::getMaze() { return _maze; }

void MazeGenerator::generateNewMaze(int width, int height)
{
	_width = width;
	_height = height;

	_maze = new int*[width];
	_visited = new bool*[width];

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

	pathForward(_startPoint);
}

MazePoint MazeGenerator::pathForward(MazePoint current)
{
	MazePoint next = choosePath(current);

	if (next.getX() != -1)
	{
		stack.push(current);
		carvePath(current, next);
		current = next;
		return pathForward(current);
	}
	else if (!stack.isEmpty())
	{
		MazePoint prev;
		prev = stack.pop();
		current = prev;
		return pathForward(current);
	}
	else
	{
		MazePoint end;
		end.setPoint(0, 0);
		return end;
	}
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

	int midX = from.getX() + dx;
	int midY = from.getY() + dy;

	_maze[midX][midY] = 0;
	_visited[midX][midY] = true;
}

MazePoint MazeGenerator::choosePath(MazePoint point)
{
	MazePoint validPoint[4];
	int counter = 0;

	// West
	if (point.getX() - 2 >= 0 && _visited[point.getX() - 2][point.getY()] == false)
		validPoint[counter++].setPoint(point.getX() - 2, point.getY());
	
	// East
	if (point.getX() + 2 < _width && _visited[point.getX() + 2][point.getY()] == false)
		validPoint[counter++].setPoint(point.getX() + 2, point.getY());

	// North
	if (point.getY() - 2 >= 0 && _visited[point.getX()][point.getY() - 2] == false)
		validPoint[counter++].setPoint(point.getX(), point.getY() - 2);

	// South
	if (point.getY() + 2 < _height && _visited[point.getX()][point.getY() + 2] == false)
		validPoint[counter++].setPoint(point.getX(), point.getY() + 2);

	// No valid paths
	if (counter == 0)
	{
		MazePoint n;
		n.setPoint(-1, -1);
		return n;
	}

	// Fill in rest?
	while (counter < 4)
		validPoint[counter++].setPoint(-1, -1);

	int num, test;
	MazePoint selected;

	do
	{
		num = rand() % 4;
		selected = validPoint[num];
		test = selected.getX();
	} while (validPoint[num].getX() == -1);

	// mark as visited
	_maze[selected.getX()][selected.getY()] = 0;
	_visited[selected.getX()][selected.getY()] = true;

	return selected;
}
