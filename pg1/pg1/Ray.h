#pragma once
class Ray
{
public:

	// r(t) = pocatek  + smerovyV *t
	Ray(void);
	Ray(Vector3 origin, Vector3 direction);
	~Ray(void);

private:
	Vector3 origin_;
	Vector3 direction_;

	float t; // REAL_MAX nastavit
};

