#include "StdAfx.h"

RayTracer::RayTracer(Cam* camera, std::vector<LightSource *> lights, std::vector<Surface *> surf)
{
	this->_camera = camera;
	this->_lights = lights;
	this->_surfaces = surf;
}

Color4 RayTracer::GetResultColor(float x, float y) {
	Ray* rayFromCamera = _camera->GenerateRay(x,y);

	Vector3 result = this->RayTrace(rayFromCamera, 0);

	return Color4(result.x, result.y, result.z,1);
}

Vector3 RayTracer::RayTrace(Ray * ray, int nest) {
	/*if (nest == 1) {
		printf("nest1");
	}
	if (nest == 2) {
		printf("nest2");
	}*/
	if (nest > MAX_NEST) return Vector3(0,0,0);
	Surface* intersectSurface = 0;
	Primitive* intersectPrimitive = 0;
	float t = 0;

	if (!GetNearestIntersection(ray, intersectSurface, intersectPrimitive, &t)) {
		return Vector3(0,0,0);
	}
	 else {
		Ray* reflectedOut = ComputeReflectedRayOut(ray, t, intersectPrimitive, intersectSurface);
		Vector3 Ir = RayTrace(reflectedOut, ++nest);

		/*Ray* reflectedIn = ComputeReflectedRayIn(ray, t, intersectPrimitive);
		Color4 It = RayTrace(reflectedIn, ++nest);*/

		Vector3 Il = ComputeLightSource(ray, t, intersectPrimitive, intersectSurface);

		float kr = 1.0f;
		float kt = 1.0f;


		return Il + kr*Ir;
	}

}

bool RayTracer::GetNearestIntersection(Ray* ray, Surface*& outSurface, Primitive*& outPrimitive, float* t_) {
	int size = _surfaces.size();
	Surface* s_nearest = 0;
	Primitive* p_nearest = 0;
	float t_nearest = 1000000000;

	for (int i = 0; i < size; i++) {
		Surface* actual = _surfaces.at(i);
		
		int triangles_size = actual->no_primitives();
		for (int j = 0; j < triangles_size; j++) {
			float t = 0;
			if (actual->get_primitives()[j]->Intersect(ray, &t) == HIT) {
				if (t < t_nearest) {
					t_nearest = t;
					s_nearest = actual;
					p_nearest = actual->get_primitives()[j];
				}
			}
		}
	}

	if (s_nearest == 0) return false;
	
	outSurface = s_nearest;
	outPrimitive = p_nearest;
	*t_ = t_nearest;
	
	return true;
}
Ray* RayTracer::ComputeReflectedRayOut(Ray* r, float t, Primitive* p, Surface* surf) {
	Vector3 pointOfIntersection = r->GetOrigin() + t*r->GetDirection();
	Vector3 normal = p->normal(pointOfIntersection);
	float c1 = -normal.DotProduct(r->GetDirection());
	
	Vector3 dir = r->GetDirection() + (2 * normal * c1);
	dir.Normalize();
	
	Ray* result = new Ray(pointOfIntersection, dir);
	return result;
}

Ray* RayTracer::ComputeReflectedRayIn(Ray* r, float t, Primitive* p, Surface* surf) {
	return r;
}

Vector3 RayTracer::ComputeLightSource(Ray* r, float t, Primitive* p, Surface* surf) {
	Material* m = surf->get_material();
	Vector3 pointOfIntersection = r->GetOrigin() + t*r->GetDirection();
	Vector3 normal = p->normal(pointOfIntersection);

	int size = _lights.size();
	Vector3 sum = Vector3(0,0,0);
	for (int i = 0; i < size; i++) {
		LightSource* actual = _lights.at(i);
		float Fatti = 1.0f;
		int n = 30;
		int Si = 1;

		Vector3 L = actual->GetOrigin();
		L.Normalize();
		float cos_fi = L.DotProduct(normal);

		Vector3 S = normal * cos_fi - L;
		S.Normalize();
		Vector3 R = 2*normal*(normal.DotProduct(L)) - L;
		Vector3 V = _camera->GetPosition();
		V.Normalize();
		float cos_alpha = V.DotProduct(R); 

		sum += Si*Fatti * actual->GetIntensity() * (m->diffuse * cos_fi + m->specular * pow(cos_alpha, n));
	}

	sum += m->diffuse * 0.001f;

	return sum;
}

RayTracer::~RayTracer(void)
{
}


