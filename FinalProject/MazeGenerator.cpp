#include "MazeGenerator.h"


int **_maze;

void MazeGenerator::generateNewMaze(int width, int height)
{
	for(int i = 0; i < width; ++i)
		_maze[i] = new int[height];

	for(int i = 0; i < width; i++)
		for(int j = 0; j < height; j++)
			_maze[i][j] = 0;


}
