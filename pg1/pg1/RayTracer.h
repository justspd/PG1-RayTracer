#pragma once
#include "stdafx.h"
#include "Cam.h"

#define MAX_NEST 2

class RayTracer
{
public:
	RayTracer(Cam* camera, std::vector<LightSource *> lights, std::vector<Surface *> surf);
	~RayTracer(void);

	Color4 GetResultColor(float x, float y);
	
private:
	bool GetNearestIntersection(Ray* ray, Surface*& outSurface, Primitive*& outPrimitive, float* t_, Surface* from);
	Vector3 RayTrace(Ray * ray, int nest, Vector3 lightFrom, Surface* s);
	Vector3 ComputeLightSource(Ray* r, float t, Primitive* p, Surface* surf);
	Ray* ComputeReflectedRayOut(Ray* r, float t, Primitive* p, Surface* surf);
	Ray* ComputeReflectedRayIn(Ray* r, float t, Primitive* p, Surface* surf);
	int isLightSourceVisible(Vector3 o, LightSource* ls, Surface* from);

	Cam* _camera;
	std::vector<LightSource *> _lights;
	std::vector<Surface *> _surfaces;
};

