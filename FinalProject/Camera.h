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

	// Navigation
	void Move(float increment);
	void Strafe (float increment);
	void Fly(float increment);
	void RotateYaw(float angle);
	void RotatePitch(float angle);

private:
	float m_x, m_y, m_z; // Position
	float m_lx, m_ly, m_lz; // Direction vector of where we are looking at
	float m_yaw, m_pitch; // Various rotation angles
	float m_strafe_lx, m_strafe_lz; // Always 90 deg to direction vector
	Maze _maze;

	bool isValidMove();
};

