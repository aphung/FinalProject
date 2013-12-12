#pragma once
struct Direction
{
	enum Type { NORTH, NORTHWEST, NORTHEAST, SOUTH, SOUTHWEST, SOUTHEAST, EAST, WEST };

	Type t_;
	Direction(Type t) : t_(t) {}
	operator Type () const { return t_; }

private:
   //prevent automatic conversion for any other built-in types such as bool, int, etc
	template<typename T>
	operator T () const;
};

