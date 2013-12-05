#pragma once

class Maze
{
public:
	Maze(void);
	~Maze(void);

	void newMaze(int width, int height); // Create new maze (input size?)
	bool travelMaze(float x, float y); // Collision detection

private:
	int _sizeWidth, _sizeHeight;
};

