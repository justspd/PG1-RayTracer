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

	ar = width/height;

	s = ar / (2*tanf(fov_y));

	axis_x_ = x;
	axis_y_ = up.CrossProduct(axis_x_);
	axis_z_ = axis_x_.CrossProduct(axis_y_);
}

Camera::~Camera(void)
{
}

Ray Camera::GenerateRay(float x, float y) {
	Vector3 dir;
	dir.x = axis_x_.x;
}
