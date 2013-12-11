/*
	Attribution: Nghia Ho and his GLUT FPS control tutorial at: http://nghiaho.com/?p=1613
*/

#pragma once
#include "Maze.h"

class Camera
{
public:
	Camera(void);
	~Camera(void);

	void Init();
	void Refresh();
	void SetPos(float x, float y, float z);
	void GetPos(float &x, float &y, float &z);
	void GetDirectionVector(float &x, float &y, float &z);
	void SetYaw(float angle);
	void SetPitch(float angle);
	void GetLookAt(float &x, float &y, float &z);

	// Navigation
	void Move(float increment, Maze &maze);
	void Strafe (float increment, Maze &maze);
	void Fly(float increment);
	void RotateYaw(float angle);
	void RotatePitch(float angle);

	// Direction
	enum Direction { NORTH, NORTHWEST, NORTHEAST, SOUTH, SOUTHWEST, SOUTHEAST, EAST, WEST };

private:
	float m_x, m_y, m_z; // Position
	float temp_x, temp_y, temp_z; // Temp position for collision detection
	float m_lx, m_ly, m_lz; // Direction vector of where we are looking at
	float m_yaw, m_pitch; // Various rotation angles
	float m_strafe_lx, m_strafe_lz; // Always 90 deg to direction vector

	bool isValidMove();
};

