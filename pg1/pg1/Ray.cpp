#include "stdafx.h"


Ray::Ray(void)
{
}


Ray::~Ray(void)
{
}

Ray::Ray(Vector3 origin, Vector3 direction) 
{
	origin_ = origin;
	direction_ = direction;
	t = REAL_MAX;
}
