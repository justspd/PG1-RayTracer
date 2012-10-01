#ifndef UTILS_H_
#define UTILS_H_

/*! \fn long long GetFileSize( const char * file_name )
\brief Vr�t� velikost souboru v bytech.
\param file_name �pln� cesta k souboru
*/
long long GetFileSize64( const char * file_name );

/*! \fn char * LTrim( char * s )
\brief O�e�e �et�zec o b�l� znaky zleva.
\param s ukazatel na �et�zec
\return Ukazatel na novou pozici v tomt� �et�zci
*/
char * RTrim( char * s );

/*! \fn char * LTrim( char * s )
\brief O�e�e �et�zec o b�l� znaky zprava.
\param s ukazatel na �et�zec
\return Ukazatel na novou pozici v tomt� �et�zci
*/
char * RTrim( char * s );

/*! \fn char * Trim( char * s )
\brief O�e�e �et�zec o b�l� znaky z obou stran.
\param s ukazatel na �et�zec
\return Ukazatel na novou pozici v tomt� �et�zci
*/
char * Trim( char *s );

#endif
