#include <stdio.h>
#include <math.h>

#include "Maze.h"

int** _maze;
bool inSquare = false;
int c_x, c_z;

Maze::Maze(void)
{
	_sizeWidth = 50; // Default size
	_sizeHeight = 50;

	c_x = -1;
	c_z = -1;
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

	// Set starting and end points
	start.setPoint(0, 0);
	end.setPoint(_sizeWidth, _sizeHeight);

	// Set visited
	_visited = new int*[width];

	for (int i = 0; i < width; ++i)
		_visited[i] = new int[height];

	for (int i = 0; i < width; i++)
		for(int j = 0; j < height; j++)
			_visited[i][j] = 0;
}

bool Maze::isValidMove(float x, float y, Direction face)
{
	// Check boundries
	if (x < -0.25 || x > _sizeWidth - 0.75)
		return false;

	if (y < -0.25 || y > _sizeHeight - 0.75)
		return false;

	// Check maze array
	int check_x = int(x + 0.5);
	int check_y = int(y + 0.5);

	if (_maze[check_x][check_y] > 0)
		return false;

	// Valid move
	return true;
}

void Maze::markMovement(float x, float z)
{
	int m_x = int(x + 0.5);
	int m_z = int(z + 0.5);

	_visited[m_x][m_z] = 1;

	//if (c_x != m_x && c_z != m_z)
	//	inSquare = false;

	//if (!inSquare)
	//{
	//	setVisitedAt(m_x, m_z, 1);
	//	inSquare = true;
	//	c_x = m_x; 
	//	c_z = m_z;
	//}

}

bool Maze::isStartPoint(float x, float z)
{
	int m_x = int(x + 0.5);
	int m_z = int(z + 0.5);

	return (start.getX() == m_x && start.getY() == m_z);
}

bool Maze::isEndPoint(float x, float z)
{
	int m_x = int(x + 0.5);
	int m_z = int(z + 0.5);

	return (end.getX() == m_x && end.getY() == m_z);
}

int Maze::getWidth() { return _sizeWidth; }
int Maze::getHeight() { return _sizeHeight; }
int **Maze::getMaze() { return _maze; }
void Maze::setVisitedAt(int x, int z, int increment) { _visited[x][z] += increment; }
int Maze::getVisitedAt(int x, int z) { return _visited[x][z]; };
