#include "stdafx.h"

// --- operátory ------

Color4 operator+( const Color4 & c1, const Color4 & c2 )
{
	return Color4( c1.r + c2.r, c1.g + c2.g, c1.b + c2.b, c1.a + c2.a );
}

Color4 operator*( const Color4 & c, const TYPE_REAL a )
{
	return Color4( a * c.r, a * c.g, a * c.b, a * c.a );
}

Color4 operator*( const TYPE_REAL a, const Color4 & c )
{
	return Color4( a * c.r, a * c.g, a * c.b, a * c.a );
}

Color4 operator*( const Vector3 & v, const Color4 & c )
{
	return Color4( v.x * c.r, v.y * c.g, v.z * c.b, c.a );
}

void operator+=( Color4 & c1, const Color4 & c2 )
{
	c1.r += c2.r;
	c1.g += c2.g;	
	c1.b += c2.b;	
	c1.a += c2.a;
}

void operator/=( Color4 & c, const TYPE_REAL a )
{
	c.r /= a;
	c.g /= a;
	c.b /= a;
	c.a /= a;
}
