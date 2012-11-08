#include "stdafx.h"

const char Material::kDiffuseMapSlot = 0;

Material::Material()
{
	// defaultní materiál
	ambient = Vector3( 0.1f, 0.1f, 0.1f );
	diffuse = Vector3( 0.4f, 0.4f, 0.4f );
	specular = Vector3( 0.8f, 0.8f, 0.8f );
	shininess = 1;

	reflectivity = 0;
	ior = -1;

	memset( textures_, 0, sizeof( *textures_ ) * NO_TEXTURES );

	name_ = "default";
}

Material::Material( std::string & name, const Vector3 & ambient, const Vector3 & diffuse,
				   const Vector3 & specular, const TYPE_REAL shininess, const TYPE_REAL ior,
				   Texture ** textures, const int no_textures )
{
	name_ = name;

	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
	this->ior = ior;
	if ( textures != NULL )
	{
		memcpy( textures_, textures, sizeof( textures ) * no_textures );
	}
}

Material::Material( std::string & name, const Vector3 & ambient, const Vector3 & diffuse,
		const Vector3 & specular, const TYPE_REAL shininess, const TYPE_REAL ior, const TYPE_REAL reflectivity,
		Texture ** textures, const int no_textures ) {
	name_ = name;

	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
	this->reflectivity = reflectivity;
	this->ior = ior;

	if ( textures != NULL )
	{
		memcpy( textures_, textures, sizeof( textures ) * no_textures );
	}
}

void Material::set_name( const char * name )
{
	name_ = std::string( name );
}

std::string Material::get_name() const
{
	return name_;
}

void Material::set_texture( const int slot, Texture * texture )
{
	textures_[slot] = texture;
}

Texture * Material::get_texture( const int slot ) const
{
	return textures_[slot];
}
