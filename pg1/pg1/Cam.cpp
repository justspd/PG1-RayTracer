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

	_matToWS = new Matrix4x4();
	_matToWS->set(0,0, 1);
	_matToWS->set(1,0, 0);
	_matToWS->set(2,0, 0);
	_matToWS->set(3,0, -position.x);

	_matToWS->set(0,1, 0);
	_matToWS->set(1,1, 1);
	_matToWS->set(2,1, 0);
	_matToWS->set(3,1, -position.y);

	_matToWS->set(0,2, 0);
	_matToWS->set(1,2, 0);
	_matToWS->set(2,2, 1);
	_matToWS->set(3,2, -position.z);

	_matToWS->set(0,3, 0);
	_matToWS->set(1,3, 0);
	_matToWS->set(2,3, 0);
	_matToWS->set(3,3, 0);
}


Ray* Cam::GenerateRay(float x, float y) {
	Vector3 dir = this->_dist * this->_direction + (0.5 - (float) y / (float) (IMG_SIZE - 1)) * (this->_cameraUp) +
                      ((float) x / (float) (IMG_SIZE - 1) - 0.5) * this->_cameraRight;

	Vector3 r = _matToWS->mult(this->_position);
	return new Ray(this->_position, dir);
}

Vector3 Cam::GetPosition() {
	return this->_position;
}

Matrix4x4* Cam::GetMatrix() {
	return _matToWS;
}


Cam::~Cam(void)
{
}
