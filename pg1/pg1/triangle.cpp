#include "stdafx.h"

Triangle::Triangle( const Vertex & v0, const Vertex & v1, const Vertex & v2, Surface * surface )
{
	vertices_[0] = v0;
	vertices_[1] = v1;
	vertices_[2] = v2;

	// pro 32bit verzi schováme ukazatel na surface do paddingu prvního vertexu
	*reinterpret_cast<Surface **>( &vertices_[0].pad ) = surface;
	// FIX: pro 64bit verzi se musí ukazatel rozdìlit mezi první dva vertexy
}

Vertex Triangle::vertex( const int i )
{
	return vertices_[i];
}

Vector3 Triangle::normal( Vector3 & p, Vector2 * texture_coord )
{		
	Vector3 v0 = vertices_[2].position - vertices_[0].position;
	Vector3 v1 = vertices_[1].position - vertices_[0].position;
	Vector3 v2 = p - vertices_[0].position;

	TYPE_REAL dot00 = v0.DotProduct( v0 );
	TYPE_REAL dot01 = v0.DotProduct( v1 );
	TYPE_REAL dot02 = v0.DotProduct( v2 );
	TYPE_REAL dot11 = v1.DotProduct( v1 );
	TYPE_REAL dot12 = v1.DotProduct( v2 );

	TYPE_REAL inv_denom = 1 / ( dot00 * dot11 - dot01 * dot01 );
	TYPE_REAL u = ( dot11 * dot02 - dot01 * dot12 ) * inv_denom;
	TYPE_REAL v = ( dot00 * dot12 - dot01 * dot02 ) * inv_denom;

	/*Vector3 n = per_vertex_normals[0] +
	u * ( per_vertex_normals[1] - per_vertex_normals[0] ) +
	v * ( per_vertex_normals[2] - per_vertex_normals[0] );
	n.Normalize();*/

	Vector3 normal = u * vertices_[2].normal +
		v * vertices_[1].normal +
		( 1 - u - v ) * vertices_[0].normal;
	normal.Normalize();

	if ( texture_coord != NULL )
	{
		*texture_coord = u * vertices_[2].texture_coords[0] +
		v * vertices_[1].texture_coords[0] +
		( 1 - u - v ) * vertices_[0].texture_coords[0];
	}

	return normal;	
}

void Triangle::applyMatrix(Matrix4x4* m) {
	vertices_[0].position = m->mult(vertices_[0].position);
	vertices_[1].position = m->mult(vertices_[1].position);
	vertices_[2].position = m->mult(vertices_[2].position);
}

Vector3 Triangle::baricenter()
{
	return ( vertices_[0].position + vertices_[1].position + vertices_[2].position ) / 3;
}

/*AABB Triangle::bounds()
{
	//TODO
}*/

Surface * Triangle::surface()
{	
	return *reinterpret_cast<Surface **>( vertices_[0].pad ); // FIX: chybí verze pro 64bit
}

int Triangle::Intersect(Ray* ray, float* t) {
	Vector3 edge1, edge2, tvec, pvec, qvec;

	Vector3 orig = ray->GetOrigin();
	Vector3 dir = ray->GetDirection();
	Vector3 vert0 = vertex(0).position;
	Vector3 vert1 = vertex(1).position;
	Vector3 vert2 = vertex(2).position;
	double det, inv_det;
	double const epsion = 0.000001;

	edge1 = vert1 - vert0;
	edge2 = vert2 - vert0;

	pvec = dir.CrossProduct(edge2);
	det = edge1.DotProduct(pvec);

	if (det > -epsion && det < epsion) return MISS;

	inv_det = 1.0/ det;

	tvec = orig - vert0;

	double u = tvec.DotProduct(pvec) * inv_det;
	if (u < 0.0 || u > 1.0) return MISS;

	qvec = tvec.CrossProduct(edge1);
	double v = dir.DotProduct(qvec) * inv_det;
	if (v < 0.0 || u+v > 1.0) return MISS;

	*t = edge2.DotProduct(qvec) * inv_det;

	return HIT;
}
