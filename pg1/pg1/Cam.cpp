#include "stdafx.h"

Cam::Cam(Vector3 position, Vector3 lookAt, Vector3 up, float fov) {
	this->_position = position;
	this->_lookAt = lookAt;
	this->_lookAt.Normalize();
	this->_up = up;
	_up.Normalize();
	this->_fov = fov;

	this->_direction = this->_lookAt - this->_position;
	this->_direction.Normalize();
	this->_cameraRight = this->_direction.CrossProduct(this->_up);
	this->_cameraRight.Normalize();
	this->_cameraUp = this->_cameraRight.CrossProduct(this->_direction);
	this->_cameraUp.Normalize();

	this->_dist = 0.5 / tan(this->_fov /2);
}


Ray* Cam::GenerateRay(float x, float y) {
	Vector3 dir = this->_dist * this->_direction + (0.5 - (float) y / (float) (IMG_SIZE - 1)) * this->_cameraUp +
                      ((float) x / (float) (IMG_SIZE - 1) - 0.5) * this->_cameraRight;
	return new Ray(this->_position, dir);
}

Vector3 Cam::GetPosition() {
	return this->_position;
}


Cam::~Cam(void)
{
}
