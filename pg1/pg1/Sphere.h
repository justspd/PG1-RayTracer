#pragma once
class Sphere : public Primitive
{
public:
	Sphere(Vector3 center, float radius, Color4 color);
	~Sphere(void);

	Vector3 GetCenter();
	float GetSqRadius();
	Material * GetMaterial();

	int Intersect(Ray* ray, float* t);
	Vector3 GetNormal(Vector3 pos);
	Color4 GetColor();

private:
	Vector3 _center;
	float _radius, _sqradius, _rradius;
	Material* _material;

	Color4 _color;
};

