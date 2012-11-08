#pragma once
#include "Sphere.h"
class EnvironmentSphere : public Sphere
{
public:
	EnvironmentSphere(Vector3 center, Vector3 up, float radius, Texture* texture = 0);
	~EnvironmentSphere(void);

	Vector3 GetColorAt(Ray* ray);
};

