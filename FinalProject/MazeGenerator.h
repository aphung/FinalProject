#pragma once

#include "MazePoint.h"

class MazeGenerator
{
public:
	MazeGenerator(void);
	~MazeGenerator(void);
	void generateNewMaze(int width, int height);

private:
	MazePoint _startPoint;
	MazePoint _current;
	int _width, _height;
	
	MazePoint MazeGenerator::choosePath(MazePoint point);
	void MazeGenerator::carvePath(MazePoint from, MazePoint to);
};

