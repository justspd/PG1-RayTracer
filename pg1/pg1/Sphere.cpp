#include "StdAfx.h"
#include "Sphere.h"


Sphere::Sphere(Vector3 center, float radius, Color4 color) {
	this->_center = center;
	this->_radius = radius;
	this->_sqradius = radius * radius;
	this->_rradius = 1.0f / radius;
	this->_color = color;
}

Color4 Sphere::GetColor() {
	return this->_color;
}

Vector3 Sphere::GetCenter() {
	return this->_center;
}
	
float Sphere::GetSqRadius() {
	return this->_sqradius;
}

int Sphere::Intersect(Ray* ray, float*  t) {
	float a = ray->GetDirection().DotProduct(ray->GetDirection());
	float b = 2* (ray->GetOrigin() - this->GetCenter()).DotProduct(ray->GetDirection());
	float c = (ray->GetOrigin() - this->GetCenter()).DotProduct(ray->GetOrigin() - this->GetCenter()) - this->GetSqRadius();

	float disc = b *b - 4*a*c;

	if (disc < 0) return MISS;

	float distSqrt = sqrtf(disc);
	float q;
	  if (b < 0)
        q = (-b - distSqrt)/2.0;
    else
        q = (-b + distSqrt)/2.0;

    float t0 = q / a;
    float t1 = c / q;

    if (t0 > t1)
    {
        float temp = t0;
        t0 = t1;
        t1 = temp;
    }

	if (t1 < 0) return MISS;
	if (t0 < 0) {
		*t = t1;
		return HIT;
	} else {
		*t = t0;
		return HIT;
	}

}

Vector3 Sphere::normal( Vector3 & p, Vector2 * texture_coord){
	Vector3 norm = (p - this->GetCenter()) * this->_rradius;
	norm.Normalize();
	return norm;

}

Sphere::~Sphere(void)
{
}
