#pragma once

class Primitive
{
public:
	Primitive(void);
	~Primitive(void);

	virtual int Intersect(Ray* ray, float* t) = 0;

};
