#pragma once
#include "stdafx.h"
class LightSource
{
public:
	LightSource(Vector3 origin, float intensity);
	~LightSource(void);

	Vector3 GetOrigin();
	Vector3 GetIntensity();

private:
	Vector3 _origin;
	float _intensity;
	
};

