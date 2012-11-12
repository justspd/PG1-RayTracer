#include "StdAfx.h"
#include "EnvironmentSphere.h"


EnvironmentSphere::EnvironmentSphere(Vector3 center, Vector3 up, float radius, std::vector<Texture*> textures) 
	: Sphere(center, radius, up, 0)
{
	this->_textures = textures;
}

Vector3 EnvironmentSphere::GetColorAt(Ray* ray) {
	Vector3 outputColor = Vector3(0,0,0);

	float a = 0.8;

	if (_textures.size() < SIDE_COUNT) {
		return outputColor;
	}

	if ((fabsf(ray->GetDirection().x) >= fabsf(ray->GetDirection().y)) 
		&& (fabsf(ray->GetDirection().x) >= fabsf(ray->GetDirection().z))) {
			if (ray->GetDirection().x > 0.0f) {
				Color4 o = _textures.at(SIDE_POSX)->get_texel(1.0f - (ray->GetDirection().z / ray->GetDirection().x+ 1.0f) * 0.5f, 
					(ray->GetDirection().y / ray->GetDirection().x+ 1.0f) * 0.5f);
				outputColor = Vector3(o.r, o.g, o.b);
			} else if (ray->GetDirection().x < 0.0f) {
				Color4 o = _textures.at(SIDE_NEGX)->get_texel(1.0f - (ray->GetDirection().z / ray->GetDirection().x+ 1.0f) * 0.5f,
					1.0f - ( ray->GetDirection().y / ray->GetDirection().x + 1.0f) * 0.5f);
				outputColor = Vector3(o.r, o.g, o.b);
			}
	} else if ((fabsf(ray->GetDirection().y) >= fabsf(ray->GetDirection().x)) && (fabsf(ray->GetDirection().y) >= fabsf(ray->GetDirection().z))) {
		if (ray->GetDirection().y > 0.0f) {
			Color4 o = _textures.at(SIDE_POSY)->get_texel((ray->GetDirection().x / ray->GetDirection().y + 1.0f) * 0.5f,
				1.0f - (ray->GetDirection().z/ ray->GetDirection().y + 1.0f) * 0.5f);
			outputColor = Vector3(o.r, o.g, o.b);
		} else if (ray->GetDirection().y < 0.0f) {
			Color4 o = _textures.at(SIDE_NEGY)->get_texel(1.0f - (ray->GetDirection().x / ray->GetDirection().y + 1.0f) * 0.5f, 
				(ray->GetDirection().z/ray->GetDirection().y + 1.0f) * 0.5f);
			outputColor = Vector3(o.r, o.g, o.b);
		}
	} else if ((fabsf(ray->GetDirection().z) >= fabsf(ray->GetDirection().x)) 
		&& (fabsf(ray->GetDirection().z) >= fabsf(ray->GetDirection().y))) {
			if (ray->GetDirection().z > 0.0f) {
				Color4 o = _textures.at(SIDE_POSZ)->get_texel((ray->GetDirection().x / ray->GetDirection().z + 1.0f) * 0.5f, 
					(ray->GetDirection().y/ray->GetDirection().z + 1.0f) * 0.5f);
				outputColor = Vector3(o.r, o.g, o.b);
			} else if (ray->GetDirection().z < 0.0f) {
				Color4 o = _textures.at(SIDE_NEGZ)->get_texel((ray->GetDirection().x / ray->GetDirection().z + 1.0f) * 0.5f, 
					1.0f - (ray->GetDirection().y /ray->GetDirection().z +1 ) * 0.5f);
				outputColor = Vector3(o.r, o.g, o.b);
			}
	}
	return outputColor;
}


EnvironmentSphere::~EnvironmentSphere(void)
{
}
