#pragma once

class Primitive
{
public:
	Primitive(void);
	~Primitive(void);

	virtual int Intersect(Ray* ray, float* t) = 0;
	virtual Vector3 normal( Vector3 & p, Vector2 * texture_coord = NULL ) = 0;
	virtual void applyMatrix(Matrix4x4* m) = 0;

};
