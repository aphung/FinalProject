#pragma once
#include "MazePoint.h"

class MazePointStack
{
public:
	MazePointStack();
	~MazePointStack(void);

	void push(MazePoint point);
	MazePoint pop();
	void display();
	bool isEmpty();

private:
	MazePoint* stack;
	int top;
	int max;

	void expandStack();
};

