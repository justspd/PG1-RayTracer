#ifndef TEXTURE_H_
#define TEXTURE_H_

/*! \class Texture
\brief Tøída popisující texturu.

\author Tomáš Fabián
\version 0.9
\date 2012
*/
class Texture
{
public:
	//! Výchozí konstruktor.
	/*!
	Inicializuje všechny složky na hodnotu nula.
	*/
	Texture();

	//! Specializovaný konstruktor.
	/*!
	Inicializuje texturu ze zadaného obrázku.

	\param image obrázek naètený pomocí OpenCV.
	*/
	Texture( IplImage * image );

	//! Destruktor.
	/*!
	Uvolní všechny alokované zdroje.
	*/
	~Texture();		

	//! Vrátí šíøku textury v pixelech.
	/*!	
	\return Šíøku textury v pixelech.
	*/
	int width() const;

		//! Vrátí výšku textury v pixelech.
	/*!	
	\return Výška textury v pixelech.
	*/
	int height() const;

	//! Vrátí ukazatel na pole pixelù formátu 8UC4.
	/*!	
	Délka øádku je \a width pixelù a poèet øádku je roven \a height pixelù.

	\return Výška textury v pixelech.
	*/
	unsigned char * get_data() const;

	//! Vrátí texel o relativních souøadnicích \a u a \a v, kde \f$(u,v)\in\left<0,1\right>^2\f$.
	/*!	
	Hodnota barvy texelu je vypoètena bilinární interpolací.

	\return Barva texelu.
	*/
	Color4 get_texel( const TYPE_REAL u, const TYPE_REAL v );

protected:

private:
	int pixel_size_; //*!< Velikost jednoho pixelu v bytech, musí se shodovat s Color4. */
	int row_size_; //*!< Délka jednoho øádku obrazu v bytech. */
	int width_; //*!< Šíøka obrazu v pixelech. */
	int height_; //*!< Výška obrazu v pixelech. */

	unsigned char * data_; //*!< Pole pixelù formátu 8UC4. */
};

/*! \fn Texture * LoadTexture( const char * file_name )
\brief Naète texturu z obrazového souboru \a file_name.
\param file_name úplná cesta k obrazovému souboru vèetnì pøípony.
*/
Texture * LoadTexture( const char * file_name );

#endif
