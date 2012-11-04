#pragma once
class Ray
{
public:

	// r(t) = pocatek  + smerovyV *t
	Ray(void);
	Ray(Vector3 origin, Vector3 direction);
	~Ray(void);

	Vector3 GetOrigin();
	Vector3 GetDirection();
	float GetT();

private:
	Vector3 _origin;
	Vector3 _direction;

	float _t; // REAL_MAX nastavit
};

