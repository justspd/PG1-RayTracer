#pragma once
#include "stdafx.h"
#include "Ray.h"

class Camera
{
public:
	Camera(void);
	Camera(Vector3 origin, Vector3 direction, Vector3 up, float fov, float aspect_ratio);
	~Camera(void);


	Ray* GenerateRay(float x, float y);

private:
	Vector3 _origin;
	Vector3 _direction;
	Vector3 _up;

	Vector3 _u;
	Vector3 _v;
	Vector3 _w;

	float _fov;
	float _aspectratio;
	float _s;
};

