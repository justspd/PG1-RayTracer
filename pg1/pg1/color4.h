#ifndef COLOR4_H_
#define COLOR4_H_

/*! \struct Color4
\brief RGBA barva.

Implementace ètyøsložkového pixelu.

\code{.cpp}
Color4 pixel = Color4( 0.5f, 0.25f, 1.0f, 1.0f );
\endcode

\author Tomáš Fabián
\version 0.9
\date 2007-2012
*/
struct /*ALIGN*/ Color4
{
public:
	union	// anonymní unie
	{
		struct
		{
			TYPE_REAL r; /*!< Èervený kanál. */
			TYPE_REAL g; /*!< Zelený kanál. */
			TYPE_REAL b; /*!< Modrý kanál. */
			TYPE_REAL a; /*!< Alfa kanál. */
		};

		TYPE_REAL data[3]; /*!< Pole složek vektoru. */
	};

	//! Výchozí konstruktor.
	/*!
	Inicializuje složky na èernou neprùhlednou barvu.
	*/
	Color4() : r( 0 ), g( 0 ), b( 0 ), a( 0 ) { }

	//! Obecný konstruktor.
	/*!
	Inicializuje barevné složky podle zadaných hodnot parametrù.	

	\param r èervený kanál.
	\param g zelený kanál.
	\param b modrý kanál.
	\param a alfa kanál.
	*/
	Color4( const TYPE_REAL r, const TYPE_REAL g, const TYPE_REAL b, const TYPE_REAL a ) : r( r ), g( g ), b( b ), a( a ) { }

	// --- operátory ------

	friend Color4 operator+( const Color4 & c1, const Color4 & c2 );
	
	friend Color4 operator*( const Color4 & c, const TYPE_REAL a );	
	friend Color4 operator*( const TYPE_REAL a, const Color4 & c );
	friend Color4 operator*( const Vector3 & v, const Color4 & c );
	
	friend void operator+=( Color4 & c1, const Color4 & c2 );	
	friend void operator/=( Color4 & c, const TYPE_REAL a );
};

#endif
