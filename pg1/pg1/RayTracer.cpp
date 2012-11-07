#include "StdAfx.h"

RayTracer::RayTracer(Cam* camera, std::vector<LightSource *> lights, std::vector<Surface *> surf)
{
	this->_camera = camera;
	this->_lights = lights;
	this->_surfaces = surf;
}

Color4 RayTracer::GetResultColor(float x, float y) {
	Ray* rayFromCamera = _camera->GenerateRay(x,y);

	Vector3 result = this->RayTrace(rayFromCamera, 0, Vector3(1,1,1), 0, 0);

	return Color4(result.x, result.y, result.z,1);
}

Vector3 RayTracer::RayTrace(Ray * ray, int nest, Vector3 lightFrom, Surface* s, Primitive* p) {
	/*if (nest == 1) {
		printf("nest1");
	}
	if (nest == 2) {
		printf("nest2");
	}
	if (nest == 3) {
		printf("nest3");
	}*/
	if (nest > MAX_NEST) return Vector3(0,0,0);
	if (lightFrom.x <=0 && lightFrom.y <= 0 && lightFrom.z <= 0) return Vector3(0,0,0);
	Surface* intersectSurface = 0;
	Primitive* intersectPrimitive = 0;
	float t = 0;

	if (!GetNearestIntersection(ray, intersectSurface, intersectPrimitive, &t, s, p)) {
		return Vector3(0,0,0);
	}
	 else {
		 if (intersectSurface == s) return Vector3(0,0,0);
		Vector3 Il = ComputeLightSource(ray, t, intersectPrimitive, intersectSurface);

		Ray* reflectedOut = ComputeReflectedRayOut(ray, t, intersectPrimitive, intersectSurface);
		Vector3 Ir = RayTrace(reflectedOut, ++nest, Il, intersectSurface, intersectPrimitive);

		/*Ray* reflectedIn = ComputeReflectedRayIn(ray, t, intersectPrimitive);
		Color4 It = RayTrace(reflectedIn, ++nest);*/

		float kr = 0.5f;
		float kt = 1.0f;


		return (Il+ (kr*Ir)) * (1.0- 1.0/nest+1);
	}

}

bool RayTracer::GetNearestIntersection(Ray* ray, Surface*& outSurface, Primitive*& outPrimitive, float* t_, Surface* from, Primitive* pfrom) {
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
				if (t < t_nearest && actual->get_primitives()[j] != pfrom) {
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

int RayTracer:: isLightSourceVisible(Vector3 o, LightSource* ls, Surface* from, Primitive * pfrom) {
	int size = _surfaces.size();

	Vector3 dir = ls->GetOrigin() - o;
	dir.Normalize();
	Ray* ray = new Ray(o, dir);

	for (int i = 0; i < size; i++) {
		Surface* actual = _surfaces.at(i);
		int triangles_size = actual->no_primitives();
		for (int j = 0; j < triangles_size; j++) {
			float t = 0;
			if (actual->get_primitives()[j]->Intersect(ray, &t) == HIT && actual->get_primitives()[j] != pfrom) {
				return 0;
			}
		}
	}
	return 1;
}

Vector3 RayTracer::ComputeLightSource(Ray* r, float t, Primitive* p, Surface* surf) {
	Material* m = surf->get_material();
	Vector3 pointOfIntersection = r->GetOrigin() + t*r->GetDirection();
	Vector3 normal = p->normal(pointOfIntersection);

	int size = _lights.size();
	Vector3 sum = Vector3(0,0,0);
	for (int i = 0; i < size; i++) {
		LightSource* actual = _lights.at(i);

		float c0 = 0;
		float c1 = 0.2f;
		float c2 = 0;
		float d = sqrt(pow(actual->GetOrigin().x - pointOfIntersection.x, 2) + pow(actual->GetOrigin().y - pointOfIntersection.y, 2) + pow(actual->GetOrigin().z - pointOfIntersection.z, 2));
		float Fatti = MIN((float) 1/(c0 + c1*d + c2*d*d), 1);
		int n = 100;
		int Si = isLightSourceVisible(pointOfIntersection, actual, surf, p);

		Vector3 L = actual->GetOrigin();
		L.Normalize();
		float cos_fi = MAX(L.DotProduct(normal), 0.0);

		Vector3 S = normal * cos_fi - L;
		S.Normalize();
		Vector3 R = 2*normal*(normal.DotProduct(L)) - L;
		Vector3 V = _camera->GetPosition();
		V.Normalize();
		float cos_alpha = MAX(V.DotProduct(R), 0.0);

		sum += Si*Fatti * actual->GetIntensity() * (m->diffuse * cos_fi + m->specular * pow(cos_alpha, n));
	}

	sum += m->diffuse * 0.2f; // ambient

	return sum;
}

RayTracer::~RayTracer(void)
{
}


