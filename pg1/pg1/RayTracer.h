#pragma once
#include "stdafx.h"
#include "Cam.h"

class RayTracer
{
public:
	RayTracer(Cam* camera, std::vector<LightSource *> lights, std::vector<Surface *> surf);
	~RayTracer(void);

	Color4 GetResultColor(float x, float y);
	
private:
	bool GetNearestIntersection(Ray* ray, Surface*& outSurface, Primitive*& outPrimitive, float* t_, Surface* from, Primitive* pfrom);
	Vector3 RayTrace(Ray * ray, int nest, Vector3 lightFrom, Surface* s,  Primitive* p);
	Vector3 ComputeLightSource(Ray* r, float t, Primitive* p, Surface* surf);
	Ray* ComputeReflectedRayOut(Ray* r, float t, Primitive* p, Surface* surf);
	Ray* ComputeReflectedRayIn(Ray* r, float t, Primitive* p, Surface* surf);
	int isLightSourceVisible(Vector3 o, LightSource* ls, Surface* from, Primitive * pfrom);

	Cam* _camera;
	std::vector<LightSource *> _lights;
	std::vector<Surface *> _surfaces;
};

