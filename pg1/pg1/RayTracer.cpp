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
		Ray* reflectedOut = ComputeReflectedRayOut(ray, t, intersectPrimitive);
		Vector3 Ir = RayTrace(reflectedOut, ++nest);

		/*Ray* reflectedIn = ComputeReflectedRayIn(ray, t, intersectPrimitive);
		Color4 It = RayTrace(reflectedIn, ++nest);*/

		Vector3 Il = ComputeLightSource(ray, t, intersectPrimitive);

		float kr = 1.0f/(nest+1);
		float kt = 1.0f/(nest+1);

		Triangle* triangle = (Triangle*) intersectPrimitive;
		Material* m = triangle->surface()->get_material();
		Vector3 ambient = m->ambient;
		Vector3 specular = m->specular;
		Vector3 diffuse = m->diffuse;

		/*int size = _lights.size();
		for (int i = 0; i < i < size; i++) {
			LightSource* actual = _lights.at(i);
			
		}*/


		return (Il*ambient + Ir* specular /*+ kt*It*/)* (1.0f/nest+1);
	}

}

bool RayTracer::GetNearestIntersection(Ray* ray, Surface*& outSurface, Primitive*& outPrimitive, float* t_) {
	int size = _surfaces.size();
	Surface* s_nearest = 0;
	Primitive* p_nearest = 0;
	float t_nearest = 1000000000;

	for (int i = 0; i < size; i++) {
		Surface* actual = _surfaces.at(i);
		
		int triangles_size = actual->no_triangles();
		for (int j = 0; j < triangles_size; j++) {
			float t = 0;
			if (actual->get_triangles()[j].Intersect(ray, &t) == HIT) {
				if (t < t_nearest) {
					t_nearest = t;
					s_nearest = actual;
					p_nearest = &actual->get_triangles()[j];
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
Ray* RayTracer::ComputeReflectedRayOut(Ray* r, float t, Primitive* p) {
	Triangle* tr = (Triangle*) p;
	Vector3 pointOfIntersection = r->GetOrigin() + t*r->GetDirection();
	Vector3 normal = tr->normal(pointOfIntersection);
	float c1 = -normal.DotProduct(r->GetDirection());
	
	Vector3 dir = r->GetDirection() + (2 * normal * c1);
	
	Ray* result = new Ray(pointOfIntersection, dir);
	return result;
}

Ray* RayTracer::ComputeReflectedRayIn(Ray* r, float t, Primitive* p) {
	return r;
}

Vector3 RayTracer::ComputeLightSource(Ray* r, float t, Primitive* p) {
	Triangle* tr = (Triangle*) p;

	/*int size = _lights.size();
	for (int i = 0; i < i < size; i++) {
		LightSource* actual = _lights.at(i);
	}*/
	float val = (1.0f/ 5.0f) * t;
	return Vector3(val, val, val);
}

RayTracer::~RayTracer(void)
{
}


