#include "stdafx.h"

TYPE_REAL Vector3::L2Norm() const
{
	return sqrt( SQR( x ) + SQR( y ) + SQR( z ) );
}

TYPE_REAL Vector3::SqrL2Norm() const
{
	return SQR( x ) + SQR( y ) + SQR( z );
}

void Vector3::Normalize()
{
	const TYPE_REAL norm = SqrL2Norm();

	if ( norm != 0 )
	{
		const TYPE_REAL rn = 1 / sqrt( norm );

		x *= rn;
		y *= rn;
		z *= rn;
	}
}

Vector3 Vector3::CrossProduct( const Vector3 & v )
{
	return Vector3(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x );
}

TYPE_REAL Vector3::DotProduct( const Vector3 & v )
{
	return x * v.x + y * v.y + z * v.z;
}

char Vector3::LargestComponent( const bool absolute_value )
{
	const Vector3 d = ( absolute_value )? Vector3( abs( x ), abs( y ), abs( z ) ) : *this;

	if ( d.x > d.y )
	{
		if ( d.x > d.z )
		{			
			return 0 ;
		}
		else
		{
			return 2;
		}
	}
	else
	{
		if ( d.y > d.z )
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}

	return -1;
}

// --- operátory ------

Vector3 operator-( const Vector3 & v )
{
	return Vector3( -v.x, -v.y, -v.z );
}

Vector3 operator+( const Vector3 & u, const Vector3 & v )
{
	return Vector3( u.x + v.x, u.y + v.y, u.z + v.z );
}

Vector3 operator-( const Vector3 & u, const Vector3 & v )
{
	return Vector3( u.x - v.x, u.y - v.y, u.z - v.z );
}

Vector3 operator*( const Vector3 & v, const TYPE_REAL a )
{
	return Vector3( a * v.x, a * v.y, a * v.z );
}

Vector3 operator*( const TYPE_REAL a, const Vector3 & v )
{
	return Vector3( a * v.x, a * v.y, a * v.z  ); 		
}

Vector3 operator*( const Vector3 & u, const Vector3 & v )
{
	return Vector3( u.x * v.x, u.y * v.y, u.z * v.z );
}

Vector3 operator/( const Vector3 & v, const TYPE_REAL a )
{
	return v * ( 1 / a );
}

void operator+=( Vector3 & u, const Vector3 & v )
{
	u.x += v.x;
	u.y += v.y;	
	u.z += v.z;	
}

void operator-=( Vector3 & u, const Vector3 & v )
{
	u.x -= v.x;
	u.y -= v.y;
	u.z -= v.z;
}

void operator*=( Vector3 & v, const TYPE_REAL a )
{
	v.x *= a;
	v.y *= a;
	v.z *= a;
}

void operator/=( Vector3 & v, const TYPE_REAL a )
{
	v.x /= a;
	v.y /= a;
	v.z /= a;
}
