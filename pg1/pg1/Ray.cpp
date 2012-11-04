#include "stdafx.h"


Ray::Ray(void)
{
}


Ray::~Ray(void)
{
}

Ray::Ray(Vector3 origin, Vector3 direction) 
{
	_origin = origin;
	_direction = direction;
	_t = REAL_MAX;
}

Vector3 Ray::GetOrigin() {
	return this->_origin;
}

Vector3 Ray::GetDirection() {
	return this->_direction;
}

float Ray::GetT() {
	return this->_t;
}
