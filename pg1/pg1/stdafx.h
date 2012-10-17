#pragma once

#define ALIGNMENT 16
#define ALIGN __declspec( align( ALIGNMENT ) )

#include "targetver.h"

#define NOMINMAX
#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <stdio.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>
#include <vector>

// opencv
#include <opencv2/opencv.hpp>

// omp
#include <omp.h>

#define DEG2RAD( x ) ( ( x ) * static_cast<TYPE_REAL>( M_PI / 180 ) )
#define RAD2DEG( x ) ( ( x ) * static_cast<TYPE_REAL>( 180 / M_PI ) )
#define SQR( x ) ( ( x ) * ( x ) )

#ifndef MIN
#define MIN( a, b ) ( ( a < b )? ( a ) : ( b ) )
#endif

#ifndef MAX
#define MAX( a, b ) ( ( a > b )? ( a ) : ( b ) )
#endif

#define TYPE_REAL float
#define REAL_MAX static_cast<TYPE_REAL>( FLT_MAX )
#define REAL_MIN static_cast<TYPE_REAL>( -FLT_MAX )
#define EPSILON static_cast<TYPE_REAL>( 1e-5 )

#define MAT_ELEM( mat, type, x, y ) reinterpret_cast<type *>( ( mat ).data + \
	( mat ).step * ( y ) + ( mat ).elemSize() * ( x ) )

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN( type_name ) \
  type_name( const type_name & ); \
  void operator=( const type_name & )

#define SAFE_DELETE_ARRAY( p ) { \
	if ( p != NULL ) \
	{ \
		delete [] p; \
		p = NULL; \
	} \
}

#include "utils.h"

#include "vector2.h"
#include "vector3.h"
#include "matrix4x4.h"
#include "quaternion.h"
#include "color4.h"

#include "texture.h"
#include "material.h"

#include "vertex.h"
#include "triangle.h"
#include "surface.h"

#include "objloader.h"

#include "Camera.h"
#include "Ray.h"
#include "AABB.h"
#include "BVH.h"
