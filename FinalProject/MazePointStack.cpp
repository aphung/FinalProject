#include "MazePointStack.h"


MazePointStack::MazePointStack()
{
	top = 0;
	max = 5;
	stack = new MazePoint[max];
}

MazePointStack::~MazePointStack() { }

void MazePointStack::push(MazePoint point)
{
	if (top == max) expandStack();
	stack[top++] = point;
}

MazePoint MazePointStack::pop()
{
	if (top == 0)
	{
		MazePoint none;
		none.setPoint(-1, -1);
		return none;
	}
	return stack[--top];
}

bool MazePointStack::isEmpty()
{
	return top == 0;
}

void MazePointStack::expandStack()
{
	MazePoint* temp = new MazePoint[max];
	for (int i = 0; i < max; i++)
		temp[i] = stack[i];

	max += 5;
	stack = new MazePoint[max];

	for (int i = 0; i < max - 5; i++)
		stack[i] = temp[i];

	delete [] temp;
}
