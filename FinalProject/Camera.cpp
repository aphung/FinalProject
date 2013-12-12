#include <stdio.h>
#include <math.h>
#include <glut.h>

#include "Camera.h"
#include "ap_pi.h"

Camera::Camera(void)
{
	Init();
}
Camera::~Camera(void)
{

}

void Camera::Init()
{
	m_yaw = 0.0;
	m_pitch = 0.0;

	SetPos(0, 1, 0);
}

// Refresh camera position
void Camera::Refresh()
{
	// Sets the camera parameter according to Riegl's coordinate system
	// x/y for flat, z for height
	m_lx = cos(m_yaw) * cos(m_pitch);
	m_ly = sin(m_pitch);
	m_lz = sin(m_yaw) * cos(m_pitch);

	m_strafe_lx = cos(m_yaw - M_PI_2);
	m_strafe_lz = sin(m_yaw - M_PI_2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(	m_x, m_y, m_z,
				m_x + m_lx, m_y + m_ly, m_z + m_lz,
				0.0, 1.0, 0.0);

	//printf("Camera: %f %f %f Direction vector: %f %f %f\n", m_x, m_y, m_z, m_lx, m_ly, m_lz);
	//printf("Camera: %f %f %f DirectionV: %f %f %f Strafe: %f %f\n", m_x, m_y, m_z, m_lx, m_ly, m_lz, m_strafe_lx, m_strafe_lz);
}

void Camera::SetPos(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;

	Refresh();
}

void Camera::GetPos(float &x, float &y, float &z)
{
	x = m_x;
	y = m_y;
	z = m_z;
}

void Camera::GetDirectionVector(float &x, float &y, float &z)
{
	x = m_lx;
	y = m_ly;
	z = m_lz;
}

void Camera::Move(float increment, Maze &maze)
{
	// Store current position
	temp_x = m_x;
	temp_y = m_y;
	temp_z = m_z;

	// Calculate new position
	float lx = cos(m_yaw) * cos(m_pitch);
	float ly = sin(m_pitch);
	float lz = sin(m_yaw) * cos(m_pitch);

	m_x = m_x + increment * lx;
	//m_y = m_y + increment * ly; // Disable flying off the y axis
	m_z = m_z + increment * lz;

	// Collision detection
	if (!maze.isValidMove(m_x, m_z, getDirection()))
	{
		m_x = temp_x;
		m_z = temp_z;
	}

	Refresh();
}

void Camera::Strafe(float increment, Maze &maze)
{
	// Store current position
	temp_x = m_x;
	temp_z = m_z;

	// Calculate new position
	m_x = m_x + increment * m_strafe_lx;
	m_z = m_z + increment * m_strafe_lz;

	// Collision detection
	if (!maze.isValidMove(m_x, m_z, getDirection()))
	{
		m_x = temp_x; // not valid return old values
		m_z = temp_z;
	}

	Refresh();
}

void Camera::Fly(float increment)
{
	m_y = m_y + increment;

	Refresh();
}

void Camera::RotateYaw(float angle)
{
	m_yaw += angle;

	Refresh();
}

void Camera::RotatePitch(float angle)
{
	const float limit = 89.0 * M_PI / 180.0;

	m_pitch += angle;

	if (m_pitch < -limit)
		m_pitch = -limit;

	if (m_pitch > limit)
		m_pitch = limit;

	Refresh();
}

void Camera::SetYaw(float angle)
{
	m_yaw = angle;

	Refresh();
}

void Camera::SetPitch(float angle)
{
	m_pitch = angle;

	Refresh();
}

Direction Camera::getDirection()
{
	Direction facing = Direction::NORTH;

	if (m_lx > -35)
	{
		if (m_lx < 35) // W or E
		{
			if (m_lz > 0) // E
				facing = Direction::EAST;
			else // W
				facing = Direction::WEST;
		}
		else // NW, N or NE
		{
			if (m_lx >= 85) // N
				facing = Direction::NORTH;
			else if (m_lz < 0) // NW
				facing = Direction::NORTHWEST;
			else // NE
				facing = Direction::NORTHEAST;

		}
	}
	else // m_lx <= -35 SW, S or SE
	{
		if (m_lx <= -85) // S
			facing = Direction::SOUTH;
		else if (m_lz < 0) // SW
			facing = Direction::SOUTHWEST;
		else // SE
			facing = Direction::SOUTHEAST;
	}

	return facing;
}
