#pragma once
class MazePoint
{
public:
	MazePoint(void);
	~MazePoint(void);
	void setPoint(int x, int y);

	int getX() { return _x; };
	void setX(int x) { _x = x; };
	int getY() { return _y; };
	void setY(int y) { _y = y; };

private:
	int _x, _y;
};

