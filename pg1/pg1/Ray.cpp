#include "stdafx.h"


Ray::Ray(void)
{
}


Ray::~Ray(void)
{
}

Ray::Ray(Vector3 origin, Vector3 direction) 
{
	_origin = origin;
	_direction = direction;
	_t = REAL_MAX;
}

bool Ray::intersect_triangle(Triangle t) {
	Vector3 edge1, edge2, tvec, pvec, qvec;
	double det, inv_det;
	double const epsion = 0.000001;

	edge1 = t.vertex(1).position-t.vertex(0).position;
	edge2 = t.vertex(2).position-t.vertex(0).position;

	pvec = _direction.CrossProduct(edge2);
	det = edge1.DotProduct(pvec);

	if (det > -epsion && det < epsion) return false;

	inv_det = 1.0/ det;

	tvec = _origin-t.vertex(0).position;

	double u = tvec.DotProduct(pvec) * inv_det;
	if (u < 0.0 || u > 1.0) return false;

	qvec = tvec.CrossProduct(edge1);
	double v = _direction.DotProduct(qvec) * inv_det;
	if (v < 0.0 || u+v > 1.0) return false;

	return true;
}
