#pragma once
#include "stdafx.h"
#include "Cam.h"
#include "EnvironmentSphere.h"

class RayTracer
{
public:
	RayTracer(Cam* camera, std::vector<LightSource *> lights, std::vector<Surface *> surf, EnvironmentSphere* env = 0);
	~RayTracer(void);

	Color4 GetResultColor(float x, float y);
	
private:
	bool GetNearestIntersection(Ray* ray, Surface*& outSurface, Primitive*& outPrimitive, float* t_, Surface* from, Primitive* pfrom);
	bool GetNearestIntersectionInSurface(Ray* ray, Surface* in, float* t, Primitive*& outPrimitive);
	Vector3 RayTrace(Ray * ray, int nest, Vector3 lightFrom, Surface* s,  Primitive* p, bool isInside, float ior_from, float ior_to);
	Vector3 ComputeLightSource(Ray* r, float t, Primitive* p, Surface* surf);
	Ray* ComputeReflectedRayOut(Ray* r, float t, Primitive* p, Surface* surf, float N1, float N2, bool isInside);
	Ray* ComputeReflectedRayIn(Ray* r, float t, Primitive* p, Surface* surf, float N1, float N2, bool isInside);
	float isLightSourceVisible(Vector3 o, LightSource* ls, Surface* from, Primitive * pfrom);

	Cam* _camera;
	std::vector<LightSource *> _lights;
	std::vector<Surface *> _surfaces;
	EnvironmentSphere* _env;
};

