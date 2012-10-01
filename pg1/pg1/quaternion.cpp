#include "stdafx.h"

Quaternion::Quaternion( Vector3 axis, const TYPE_REAL angle )
{
	axis.Normalize();

	const TYPE_REAL half_angle = angle * static_cast<TYPE_REAL>( 0.5 );
	const TYPE_REAL sin_half_angle = sin( half_angle );

	x = axis.x * sin_half_angle;
	y = axis.y * sin_half_angle;
	z = axis.z * sin_half_angle;
	w = cos( half_angle );
}

Quaternion::Quaternion( const TYPE_REAL pitch, const TYPE_REAL yaw, const TYPE_REAL roll )
{
	float p = pitch * static_cast<TYPE_REAL>( 0.5 );
	float y = yaw * static_cast<TYPE_REAL>( 0.5 );
	float r = roll * static_cast<TYPE_REAL>( 0.5 );
 
	float sin_p = sin( p );
	float sin_y = sin( y );
	float sin_r = sin( r );
	float cos_p = cos( p );
	float cos_y = cos( y );
	float cos_r = cos( r );
 
	x = sin_r * cos_p * cos_y - cos_r * sin_p * sin_y;
	y = cos_r * sin_p * cos_y + sin_r * cos_p * sin_y;
	z = cos_r * cos_p * sin_y - sin_r * sin_p * cos_y;
	w = cos_r * cos_p * cos_y + sin_r * sin_p * sin_y;
 
	Normalize();
}

TYPE_REAL Quaternion::Norm()
{
	return sqrt( SQR( x ) + SQR( y ) + SQR( z ) + SQR( w ) );
}

TYPE_REAL Quaternion::SqrNorm()
{
	return SQR( x ) + SQR( y ) + SQR( z ) + SQR( w );
}

void Quaternion::Conjugation()
{
	x *= -1;
	y *= -1;
	z *= -1;
}

void Quaternion::Normalize()
{
	const TYPE_REAL norm = SqrNorm();

	if ( norm != 0 )
	{
		const TYPE_REAL rn = 1 / sqrt( norm );

		x *= rn;
		y *= rn;
		z *= rn;
		w *= rn;
	}
}

Vector3 Quaternion::ToVector3()
{
	return Vector3( x, y, z );
}

Matrix4x4 Quaternion::ToMatrix4x4()
{
	Quaternion q = *this;
	q.Normalize();

	const TYPE_REAL x2 = SQR( q.x );
	const TYPE_REAL y2 = SQR( q.y );
	const TYPE_REAL z2 = SQR( q.z );
	const TYPE_REAL xy = q.x * q.y;
	const TYPE_REAL xz = q.x * q.z;
	const TYPE_REAL yz = q.y * q.z;
	const TYPE_REAL wx = q.w * q.x;
	const TYPE_REAL wy = q.w * q.y;
	const TYPE_REAL wz = q.w * q.z;

	return Matrix4x4( 1 - 2 * ( y2 + z2 ), 2 * ( xy + wz ), 2 * ( xz - wy ), 0,
		2 * ( xy - wz ), 1 - 2 * ( x2 + z2 ), 2 * ( yz + wx ), 0,
		2 * ( xz + wy ), 2 * ( yz - wx ), 1 - 2 * ( x2 + y2 ), 0,
		0, 0, 0, 1 );
}

// --- operátory ------

Quaternion operator*( const Quaternion & u, const Quaternion & v )
{
	return Quaternion( u.w * v.x + u.x * v.w + u.y * v.z - u.z * v.y,
		u.w * v.y - u.x * v.z + u.y * v.w + u.z * v.x,
		u.w * v.z + u.x * v.y - u.y * v.x + u.z * v.w,
		u.w * v.w - u.x * v.x - u.y * v.y - u.z * v.z );
}

void operator*=( Quaternion & u, const Quaternion v )
{
	u = Quaternion( u.w * v.x + u.x * v.w + u.y * v.z - u.z * v.y,
		u.w * v.y - u.x * v.z + u.y * v.w + u.z * v.x,
		u.w * v.z + u.x * v.y - u.y * v.x + u.z * v.w,
		u.w * v.w - u.x * v.x - u.y * v.y - u.z * v.z );	
}