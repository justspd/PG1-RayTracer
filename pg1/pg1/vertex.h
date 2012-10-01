#ifndef VERTEX_H_
#define VERTEX_H_

/*! \def NO_TEXTURE_COORDS
\brief Poèet texturovacích souøadnic.
*/
#define NO_TEXTURE_COORDS 1

/*! \struct Vertex
\brief Struktura popisující všechny atributy vertexu.

\author Tomáš Fabián
\version 0.9
\date 2012
*/
struct /*ALIGN*/ Vertex
{
public:
	Vector3 position; /*!< Pozice vertexu. */
	Vector3 normal; /*!< Normála vertexu. */
	Vector3 color; /*!< RGB barva vertexu <0, 1>^3. */
	Vector2 texture_coords[NO_TEXTURE_COORDS]; /*!< Texturovací souøadnice. */

	char pad[4]; // doplnìní na 48 bytù, mìlo by to mít alespoò 4 byty, aby se sem vešel ukazatel

	//! Výchozí konstruktor.
	/*!
	Inicializuje všechny složky vertexu na hodnotu nula.
	*/
	Vertex() { }

	//! Obecný konstruktor.
	/*!
	Inicializuje vertex podle zadaných hodnot parametrù.

	\param position pozice vertexu.
	\param normal normála vertexu.
	\param color barva vertexu.
	\param texture_coords nepovinný ukazatel na pole texturovacích souøadnic.
	*/
	Vertex( const Vector3 & position, const Vector3 & normal, Vector3 & color, Vector2 * texture_coords = NULL );
};

#endif
