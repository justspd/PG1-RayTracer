#pragma once
#include "stdafx.h"
class LightSource
{
public:
	LightSource(Vector3 origin);
	~LightSource(void);

	Vector3 GetOrigin();

private:
	Vector3 _origin;
	Material _material;
};

