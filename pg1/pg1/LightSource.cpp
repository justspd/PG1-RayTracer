#include "StdAfx.h"
#include "LightSource.h"


LightSource::LightSource(Vector3 origin, float intensity)
{
	this->_origin = origin;
	this->_intensity = intensity;
}

Vector3 LightSource::GetOrigin() {
	return this->_origin;
}

Vector3 LightSource::GetIntensity() {
	return Vector3(_intensity, _intensity, _intensity);
}


LightSource::~LightSource(void)
{
}
