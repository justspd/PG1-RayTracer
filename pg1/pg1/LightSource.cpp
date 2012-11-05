#include "StdAfx.h"
#include "LightSource.h"


LightSource::LightSource(Vector3 origin)
{
	this->_origin = origin;
	_material.ambient = Vector3(100,100,100);
	_material.diffuse = Vector3(100,100,100);
	_material.reflectivity = 100;
	_material.ior = 100;
	_material.specular = Vector3(100,100,100);
	_material.shininess = 100;
}

Vector3 LightSource::GetOrigin() {
	return this->_origin;
}


LightSource::~LightSource(void)
{
}
