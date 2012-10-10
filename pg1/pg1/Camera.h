#pragma once
#include "stdafx.h"
#include "Ray.h"

class Camera
{
public:
	Camera(void);
	Camera(int width, int height, float fov_y, Vector3 eye, Vector3 up, Vector3 z);
	~Camera(void);


	Ray* GenerateRay(float x, float y);

private:
	Vector3 _eye; //[WS]
	int _width;
	int _height;

	Vector3 _axis_z; // [WS]
	Vector3 _up; // ukazuje, kde je nahoru
	Vector3 _axis_y; // axis_z_ X x    znormlaizovat
	Vector3 _axis_x; // axis_y_ X axis_z_     znormalizovat

	float _fov_y; // [rad] sirka zaberu kamery

	float _s;
	float _ar;
};

