#ifndef COLOR4_H_
#define COLOR4_H_

/*! \struct Color4
\brief RGBA barva.

Implementace �ty�slo�kov�ho pixelu.

\code{.cpp}
Color4 pixel = Color4( 0.5f, 0.25f, 1.0f, 1.0f );
\endcode

\author Tom� Fabi�n
\version 0.9
\date 2007-2012
*/
struct /*ALIGN*/ Color4
{
public:
	union	// anonymn� unie
	{
		struct
		{
			TYPE_REAL r; /*!< �erven� kan�l. */
			TYPE_REAL g; /*!< Zelen� kan�l. */
			TYPE_REAL b; /*!< Modr� kan�l. */
			TYPE_REAL a; /*!< Alfa kan�l. */
		};

		TYPE_REAL data[3]; /*!< Pole slo�ek vektoru. */
	};

	//! V�choz� konstruktor.
	/*!
	Inicializuje slo�ky na �ernou nepr�hlednou barvu.
	*/
	Color4() : r( 0 ), g( 0 ), b( 0 ), a( 0 ) { }

	//! Obecn� konstruktor.
	/*!
	Inicializuje barevn� slo�ky podle zadan�ch hodnot parametr�.	

	\param r �erven� kan�l.
	\param g zelen� kan�l.
	\param b modr� kan�l.
	\param a alfa kan�l.
	*/
	Color4( const TYPE_REAL r, const TYPE_REAL g, const TYPE_REAL b, const TYPE_REAL a ) : r( r ), g( g ), b( b ), a( a ) { }

	// --- oper�tory ------

	friend Color4 operator+( const Color4 & c1, const Color4 & c2 );
	
	friend Color4 operator*( const Color4 & c, const TYPE_REAL a );	
	friend Color4 operator*( const TYPE_REAL a, const Color4 & c );
	friend Color4 operator*( const Vector3 & v, const Color4 & c );
	
	friend void operator+=( Color4 & c1, const Color4 & c2 );	
	friend void operator/=( Color4 & c, const TYPE_REAL a );
};

#endif
