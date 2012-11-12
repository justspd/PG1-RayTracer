#include "StdAfx.h"
#include "EnvironmentSphere.h"


EnvironmentSphere::EnvironmentSphere(Vector3 center, Vector3 up, float radius, Texture* texture) 
	: Sphere(center, radius, up, texture)
{
}

Vector3 EnvironmentSphere::GetColorAt(Ray* ray) {
	Vector3 outputColor = Vector3(0,0,0);

	float a = 0.8;

	if (_texture == 0) {
		return outputColor;
	}

	float t = 0;
	if (Intersect(ray, &t)) {
		if (t > 0) {
			Vector3 intersect = ray->GetOrigin() + t*ray->GetDirection();
			float u = a*cos(intersect.z / this->_radius) / 3.1415;
			float v = a*cos(intersect.x/ (this->_radius* sin(3.1415*u))) / 2*3.14;

			Color4 res = _texture->get_texel(u, v);
			outputColor = Vector3(res.r, res.g, res.b);
		}
	}
	//Color4 c = _texture->get_texel(1.0f - (ray->GetDirection().z /ray->GetDirection().x+ 1.0f) * 0.5f, (ray->GetDirection().y /ray->GetDirection().x+ 1.0f) * 0.5f);
	//Color4 c = _texture->get_texel(fabs(ray->GetDirection().x), fabs(ray->GetDirection().y));
	return outputColor;
}


EnvironmentSphere::~EnvironmentSphere(void)
{
}
