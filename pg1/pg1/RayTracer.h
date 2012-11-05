#pragma once
#include "stdafx.h"
#include "Cam.h"

#define MAX_NEST 4

class RayTracer
{
public:
	RayTracer(Cam* camera, std::vector<LightSource *> lights, std::vector<Surface *> surf);
	~RayTracer(void);

	Color4 GetResultColor(float x, float y);
	
private:
	bool GetNearestIntersection(Ray* ray, Surface*& outSurface, Primitive*& outPrimitive, float* t_);
	Vector3 RayTrace(Ray * ray, int nest);
	Vector3 ComputeLightSource(Ray* r, float t, Primitive* p);
	Ray* ComputeReflectedRayOut(Ray* r, float t, Primitive* p);
	Ray* ComputeReflectedRayIn(Ray* r, float t, Primitive* p);

	Cam* _camera;
	std::vector<LightSource *> _lights;
	std::vector<Surface *> _surfaces;
};

