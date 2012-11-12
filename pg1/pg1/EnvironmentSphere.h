#pragma once
#include "Sphere.h"
class EnvironmentSphere : public Sphere
{
public:
	EnvironmentSphere(Vector3 center, Vector3 up, float radius, std::vector<Texture*> textures);
	~EnvironmentSphere(void);

	Vector3 GetColorAt(Ray* ray);
private:
	std::vector<Texture*> _textures;
};

