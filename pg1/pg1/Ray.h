#pragma once
class Ray
{
public:

	// r(t) = pocatek  + smerovyV *t
	Ray(void);
	Ray(Vector3 origin, Vector3 direction);
	~Ray(void);

	bool intersect_triangle(Triangle t);

private:
	Vector3 _origin;
	Vector3 _direction;

	float _t; // REAL_MAX nastavit
};

