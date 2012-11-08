#include "StdAfx.h"
#include "EnvironmentSphere.h"


EnvironmentSphere::EnvironmentSphere(Vector3 center, Vector3 up, float radius, Texture* texture) 
	: Sphere(center, radius, up, texture)
{
}

Vector3 EnvironmentSphere::GetColorAt(Ray* ray) {
	Vector3 outputColor = Vector3(0,0,0);

	if (_texture == 0) {
		return outputColor;
	}

	Color4 c = _texture->get_texel(fabs(ray->GetDirection().x), fabs(ray->GetDirection().y));
	return Vector3(c.r, c.g, c.g);
}


EnvironmentSphere::~EnvironmentSphere(void)
{
}
