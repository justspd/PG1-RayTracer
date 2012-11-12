#ifndef MATRIX_H_
#define MATRIX_H_

/*! \class Matrix4x4
\brief Re�ln� matice 4x4 uspo��dan� po ��dc�ch.

\author Tom� Fabi�n
\version 0.9
\date 2012
*/
class Matrix4x4
{
public:
	//! V�choz� konstruktor.
	/*!
		Inicializace na matici identity.
	*/
	Matrix4x4();

	//! V�choz� konstruktor.
	/*!
		Inicializace matice zadan�mi hodnotami. Prvn� index ozna�uje ��dek, druh� index pat�� sloupci.
	*/
	Matrix4x4( const TYPE_REAL m00, const TYPE_REAL m01, const TYPE_REAL m02, const TYPE_REAL m03, 
		const TYPE_REAL m10, const TYPE_REAL m11, const TYPE_REAL m12, const TYPE_REAL m13, 
		const TYPE_REAL m20, const TYPE_REAL m21, const TYPE_REAL m22, const TYPE_REAL m23,
		const TYPE_REAL m30, const TYPE_REAL m31, const TYPE_REAL m32, const TYPE_REAL m33 );

	//! Transpozice matice.
	/*!
		Provede traspozici matice vz�jemnou v�m�nou ��dk� a sloupc�.
	*/
	void Transpose();

	//! Euklidovsk� inverze matice.
	/*!
		Provede inverzi matice. V�sledek je spr�vn� jen za p�edpokladu, �e se jedn� o matici
		p�edstavuj�c� Euklidovsk� transformace zahrnuj�c� translaci,
		rotaci a reflexi. Takov� transformace m�n� pouze orientaci a pozici objekt�, �hly a
		d�lky z�st�vaj� zachov�ny.
	*/
	void EuclideanInverse();

	//! Nastav� zadan� prvek matice na novou hodnotu.
	/*!
		\param row ��dek matice.
		\param column sloupec matice.
		\param value nov� hodnota prvku matice.
	*/
	Vector3 mult(Vector3 v);
	void set( const int row, const int column, const TYPE_REAL value );

	//! Ukazatel na prvky matice.
	/*!
		\return Ukazatel na prvky matice.
	*/
	TYPE_REAL * data();

	friend Matrix4x4 operator*( const Matrix4x4 & a, const Matrix4x4 & b );

private:
	union
	{
		/* Row-major
		m00 m01 m02 m03
		m10 m11 m12 m13
		m20 m21 m22 m23
		m30 m31 m32 m33
		*/

		struct
		{
			TYPE_REAL m00_;
			TYPE_REAL m01_;
			TYPE_REAL m02_;
			TYPE_REAL m03_;

			TYPE_REAL m10_;
			TYPE_REAL m11_;
			TYPE_REAL m12_;
			TYPE_REAL m13_;

			TYPE_REAL m20_;
			TYPE_REAL m21_;
			TYPE_REAL m22_;
			TYPE_REAL m23_;

			TYPE_REAL m30_;
			TYPE_REAL m31_;
			TYPE_REAL m32_;
			TYPE_REAL m33_;
		};

		TYPE_REAL data_[4 * 4];
	};
};

typedef Matrix4x4 Matrix4;

#endif
