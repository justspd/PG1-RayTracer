#include "stdafx.h"

Camera::Camera(void)
{

}

Camera::Camera(int width, int height, float fov_y, Vector3 eye, Vector3 up, Vector3 x, Vector3 y, Vector3 z)
{
	width_ = width;
	height_ = height;
	fov_y_ = fov_y;
	eye_ = eye;
	up_ = up;
	
	axis_x_ = x;

	axis_y_ = y;
	axis_z_ = z;
}

Camera::~Camera(void)
{
}
