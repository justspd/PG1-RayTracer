#pragma once
class Ray
{
public:

	// r(t) = pocatek  + smerovyV *t
	Ray(void);
	~Ray(void);

private:
	Vector3 origin_;
	Vector3 direction_;

	float t; // REAL_MAX nastavit
};

