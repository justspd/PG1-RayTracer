#pragma once
#include "stdafx.h"
#include "Ray.h"

class Cam
{
public:
	Cam(Vector3 position, Vector3 lookAt, Vector3 up, float fov);

	Ray* GenerateRay(float x, float y);
	~Cam(void);

private:
	Vector3 _position;
	Vector3 _lookAt;
	Vector3 _up;
	Vector3 _direction;
	Vector3 _cameraRight;
	Vector3 _cameraUp;
	
	float _fov;
	float _dist;

};

