#ifndef QUATERNION_H_
#define QUATERNION_H_

/*! \struct Quaternion
\brief Trojrozmìrný (3D) vektor.

Implementace kvaternionu jakožto nekomutativní ètyøsložkového zobecnìní komplexních èísel.
Jedná se o lineární kombinaci prvkù 1, \f$\mathbf{i}\f$, \f$\mathbf{j}\f$ a \f$\mathbf{k}\f$ 
Kvaternion \f$\mathbf{q}\f$ zapisujeme \f$w + x\mathbf{i} + y\mathbf{j} + z\mathbf{k}\f$
nebo ve zkráceném tvaru \f$\mathbf{q}= (w, \mathbf{v}\f$), kde \f$w \in \mathbb{R}\f$ a \f$\mathbf{v}=(x, y, z)\f$.
Vektor \f$\mathbf{v}\f$ mužeme tedy chápat jako vektor v \f$\mathbb{R}^3\f$.

Pøíklad rotace vektoru kolem libovolné osy
\code{.cpp}
Vector3 axis = Vector3( 2, 0, 2 );		
Vector3 u = Vector3( 1, 0, 0 );
Quaternion q = Quaternion( u );
Quaternion r = Quaternion( axis, DEG2RAD( 90 ) );		
Quaternion w = r * q;
r.Conjugation();
w *= r;
Vector3 v = w.ToVector3(); // vektor u otoèený kole osy axis o angle stupnòù (cw)
\endcode

\author Tomáš Fabián
\version 0.9
\date 2007-2012
*/
struct /*ALIGN*/ Quaternion
{
public:
	union	// anonymní unie
	{
		struct
		{
			TYPE_REAL x; /*!< První složka kvaternionu. */
			TYPE_REAL y; /*!< Druhá složka kvaternionu. */
			TYPE_REAL z; /*!< Tøetí složka kvaternionu. */
			TYPE_REAL w; /*!< Skalár. */
		};

		TYPE_REAL data[4]; /*!< Pole složek kvaternionu. */
	};

	//! Výchozí konstruktor.
	/*!
	Inicializuje všechny složky kvaternionu na hodnotu nula.
	*/
	Quaternion() : x( 0 ), y( 0 ), z( 0 ), w( 0 ) { }	

	//! Obecný konstruktor.
	/*!
	Inicializuje složky kvaternionu podle zadaných hodnot parametrù.

	\param x první složka kvaternionu.
	\param y druhá složka kvaternionu.
	\param z tøetí složka kvaternionu.
	\param w skalární složka kvaternionu.
	*/
	Quaternion( const TYPE_REAL x, const TYPE_REAL y, const TYPE_REAL z, const TYPE_REAL w ) : x( x ), y( y ), z( z ), w( w ) { }

	//! Konstruktor.
	/*!
	Inicializuje složky kvaternionu podle zadaného vektoru.

	\param v vektor.
	*/
	Quaternion( const Vector3 & v ) : x( v.x ), y( v.y ), z( v.z ), w( 0 ) { }

	//! Konstruktor rotaèního kvaternionu.
	/*!
	Inicializuje složky kvaternionu podle zadané osy rotace a úhlu.

	\param axis vektor reprezentující osu rotace.
	\param angle úhel rotace.
	*/
	Quaternion( Vector3 axis, const TYPE_REAL angle );

	//! Konstruktor kvaternionu z Eulerových úhlù.
	/*!
	Inicializuje složky kvaternionu podle zadaných Eulerových úhlù.

	\param pitch úhel stopání.
	\param yaw úhel vyboèení.
	\param roll úhel natoèení.
	*/
	Quaternion( const TYPE_REAL pitch, const TYPE_REAL yaw, const TYPE_REAL roll );

	//! Norma kvaternionu.
	/*!
	\return x Hodnotu \f$\mathbf{|q|}=\sqrt{\mathbf{q} \={\mathbf{q}}\f$.
	*/
	TYPE_REAL Norm();

	//! Druhá mocnina normy kvaternionu.
	/*!
	\return x Hodnotu \f$\mathbf{|q|}^2=\mathbf{q} \={\mathbf{q}\f$.
	*/
	TYPE_REAL SqrNorm();

	//! Konjugace.
	/*!
	\return Hodnotu \f$\={\mathbf{q}\f$.
	*/
	void Conjugation();

	//! Normalizace kvaternionu.
	/*!
	Po provedení operace bude mít vektor jednotkovou délku.
	*/
	void Normalize();

	//! Pøevede kvaternion na 3D vektor.
	/*!
	\return Vektor\f$\mathbf{v}=(x,y,z)\f$.
	*/
	Vector3 ToVector3();

	//! Pøevede kvaternion na matici.
	/*!
	\return Vektor\f$(x,y,z)\f$.
	*/
	Matrix4x4 ToMatrix4x4();

	// --- operátory ------
	
	friend Quaternion operator*( const Quaternion & u, const Quaternion & v );

	friend void operator*=( Quaternion & u, const Quaternion v );	
};

#endif
