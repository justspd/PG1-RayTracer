#ifndef VECTOR2_H_
#define VECTOR2_H_

/*! \struct Vector2
\brief Dvourozm�rn� (2D) vektor.

Implementace dvouslo�kov�ho re�ln�ho vektoru podporuj�c� z�kladn�
matematick� operace.

\note
Vektor se pova�uje za sloupcov�, p�esto�e je v koment���ch pro jednoduchost
uv�d�n jako ��dkov�.

\code{.cpp}
Vector2 v = Vector2( 2.0f, 4.5f );
v.Normalize();
\endcode

\author Tom� Fabi�n
\version 0.9
\date 2007-2012
*/
struct /*ALIGN*/ Vector2
{
public:
	union	// anonymn� unie
	{
		struct
		{
			TYPE_REAL x; /*!< Prvn� slo�ka vektoru. */
			TYPE_REAL y; /*!< Druh� slo�ka vektoru. */
		};

		TYPE_REAL data[2]; /*!< Pole slo�ek vektoru. */
	};

	//! Implicitn� konstruktor.
	/*!
	Inicializuje v�echny slo�ky vektoru na hodnotu nula,
	\f$\mathbf{v}=\mathbf{0}\f$.
	*/
	Vector2() : x( 0 ), y( 0 ) { }	

	//! Obecn� konstruktor.
	/*!
	Inicializuje slo�ky vektoru podle zadan�ch hodnot parametr�,
	\f$\mathbf{v}=(x,y)\f$.

	\param x prvn� slo�ka vektoru.
	\param y druh� slo�ka vektoru.
	*/
	Vector2( const TYPE_REAL x, const TYPE_REAL y ) : x( x ), y( y ) { }

	//! L2-norma vektoru.
	/*!
	\return x Hodnotu \f$\mathbf{||v||}=\sqrt{x^2+y^2}\f$.
	*/
	TYPE_REAL L2Norm();

	//! Druh� mocnina L2-normy vektoru.
	/*!
	\return Hodnotu \f$\mathbf{||v||^2}=x^2+y^2\f$.
	*/
	TYPE_REAL SqrL2Norm();

	//! Normalizace vektoru.
	/*!
	Po proveden� operace bude m�t vektor jednotkovou d�lku.
	*/
	void Normalize();

	//! Vektorov� sou�in.
	/*!
	\param v vektor \f$\mathbf{v}\f$.

	\return Hodnotu \f$\mathbf{u}_x \mathbf{v}_y + \mathbf{u}_y \mathbf{v}_x\f$.
	*/
	TYPE_REAL CrossProduct( const Vector2 & v );

	//! Vektorov� sou�in.
	/*!
	\note Plyne z v�po�tu determinantu matice \f$2\times2\f$.

	\return Hodnotu \f$(\mathbf{u}_y, -\mathbf{u}_x)\f$.
	*/
	Vector2 CrossProduct();

	//! Skal�rn� sou�in.
	/*!		
	\return Hodnotu \f$\mathbf{u}_x \mathbf{v}_x + \mathbf{u}_y \mathbf{v}_y)\f$.
	*/
	TYPE_REAL DotProduct( const Vector2 & v );

	//! Rotace.
	/*!		
	\return Vektor orotovan� kolem po��tku o \f$\phi\f$ radi�n� v kladn�m smyslu.
	*/
	Vector2 Rotate( const TYPE_REAL phi );

	//! Index nejv�t�� slo�ky vektoru.
	/*!
	\param absolute_value index bude ur�en podle absolutn� hodnoty slo�ky

	\return Index nejv�t�� slo�ky vektoru.
	*/
	char LargestComponent( const bool absolute_value = false );	

	//void Print();

	// --- oper�tory ------

	friend Vector2 operator-( const Vector2 & v );

	friend Vector2 operator+( const Vector2 & u, const Vector2 & v );
	friend Vector2 operator-( const Vector2 & u, const Vector2 & v );

	friend Vector2 operator*( const Vector2 & v, const TYPE_REAL a );	
	friend Vector2 operator*( const TYPE_REAL a, const Vector2 & v );
	friend Vector2 operator*( const Vector2 & u, const Vector2 & v );

	friend Vector2 operator/( const Vector2 & v, const TYPE_REAL a );

	friend void operator+=( Vector2 & u, const Vector2 & v );
	friend void operator-=( Vector2 & u, const Vector2 & v );
	friend void operator*=( Vector2 & v, const TYPE_REAL a );
	friend void operator/=( Vector2 & v, const TYPE_REAL a );	
};

#endif
