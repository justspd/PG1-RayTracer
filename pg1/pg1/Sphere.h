#pragma once
class Sphere : public Primitive
{
public:
	Sphere(Vector3 center, float radius, Color4 color);
	~Sphere(void);

	Vector3 GetCenter();
	float GetSqRadius();

	int Intersect(Ray* ray, float* t);
	Color4 GetColor();

	Vector3 normal( Vector3 & p, Vector2 * texture_coord = NULL );

private:
	Vector3 _center;
	float _radius, _sqradius, _rradius;

	Color4 _color;
};

