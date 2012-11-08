#pragma once
class Sphere : public Primitive
{
public:
	Sphere(Vector3 center, float radius, Vector3 up);
	Sphere(Vector3 center, float radius, Vector3 up,Texture* texture);
	~Sphere(void);

	Vector3 GetCenter();
	float GetSqRadius();
	Texture* GetTexture();

	int Intersect(Ray* ray, float* t);

	Vector3 normal( Vector3 & p, Vector2 * texture_coord = NULL );

protected:
	Vector3 _center, _up;
	float _radius, _sqradius, _rradius;

	Texture* _texture;
};

