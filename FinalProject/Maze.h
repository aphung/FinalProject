#pragma once

class Maze
{
public:
	Maze(void);
	~Maze(void);

	void newMaze(int width, int height); // Create new maze (input size?)
	bool isValidMove(float x, float y); // Collision detection

	int getWidth();
	int getHeight();

private:
	int _sizeWidth, _sizeHeight;

	bool isWithinBoundry(float x, float y);
};

