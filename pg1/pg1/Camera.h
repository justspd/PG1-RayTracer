#pragma once

#include "Ray.h"
#include "Vector3.h"

class Camera
{
public:
	Camera(void);
	Camera(int width, int height, float fov_y, Vector3 eye, Vector3 up, Vector3 x, Vector3 y, Vector3 z);
	~Camera(void);

	Ray GenerateRay(float x, float y);

private:
	Vector3 eye_; //[WS]
	int width_;
	int height_;

	Vector3 axis_z_; // [WS]
	Vector3 up_; // ukazuje, kde je nahoru
	Vector3 axis_y_; // axis_z_ X x    znormlaizovat
	Vector3 axis_x_; // axis_y_ X axis_z_     znormalizovat

	float fov_y_; // [rad] sirka zaberu kamery
};

