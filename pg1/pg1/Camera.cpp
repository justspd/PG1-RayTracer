#include "stdafx.h"

Camera::Camera(void)
{

}

Camera::Camera(Vector3 origin, Vector3 direction, Vector3 up, float fov, float aspect_ratio)
{
	_origin = origin;
	_direction = direction;
	_direction.Normalize();

	_up = up;
	_up.Normalize();
	_fov = fov;
	_aspectratio = aspect_ratio;

	this->_w = direction;
	this->_u = up.CrossProduct(_w);
	this->_u.Normalize();
	this->_v = _w.CrossProduct(_u);
	this->_v.Normalize();
	this->_s = aspect_ratio / (2*tan(fov));

}

Camera::~Camera(void)
{
}

Ray* Camera::GenerateRay(float x, float y) {
	Vector3 direction; 
	direction.x = this->_u.x*(x*0.5*this->_aspectratio) + this->_v.x*(y*0.5) + this->_w.x*-this->_s; 
	direction.y = this->_u.y*(x*0.5*this->_aspectratio) + this->_v.y*(y*0.5) + this->_w.y*-this->_s; 
	direction.z = this->_u.z*(x*0.5*this->_aspectratio) + this->_v.z*(y*0.5) + this->_w.z*-this->_s; 
	direction.Normalize();
	Ray* result = new Ray(this->_origin, direction);
	return result;
}
