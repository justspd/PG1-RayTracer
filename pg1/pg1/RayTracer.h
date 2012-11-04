#pragma once
class RayTracer
{
public:
	RayTracer(void);
	~RayTracer(void);

	Primitive* GetNearestPrimitive(Ray* ray, std::vector<Primitive *> objects);
};

