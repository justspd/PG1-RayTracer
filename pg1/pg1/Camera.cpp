#include "stdafx.h"

Camera::Camera(void)
{

}

Camera::Camera(int width, int height, float fov_y, Vector3 eye, Vector3 up, Vector3 z)
{

	_width = width;
	_height = height;
	_fov_y = fov_y;
	_eye = eye;
	_up = up;

	_eye.Normalize();
	_up.Normalize();

	_ar = (float)width / (float) height;
	_s = _ar / (2*tanf(_fov_y));
	
	_axis_z = z;
	_axis_z.Normalize();
	_axis_x = up.CrossProduct(z);
	_axis_x.Normalize();
	_axis_y = z.CrossProduct(_axis_y);
	_axis_y.Normalize();

}

Camera::~Camera(void)
{
}

Ray* Camera::GenerateRay(float x, float y) {
	
	Vector3 dir;
	dir.x = ((2.0f * (float)x) - (float)_width) / (float)_width * tanf(_fov_y);
	dir.y = ((2.0f * (float)y) - (float)_height) / (float)_height * tanf(_fov_y);
	dir.z = -1;
	return NULL;
}
