#ifndef UTILS_H_
#define UTILS_H_

/*! \fn long long GetFileSize( const char * file_name )
\brief Vrátí velikost souboru v bytech.
\param file_name Úplná cesta k souboru
*/
long long GetFileSize64( const char * file_name );

/*! \fn char * LTrim( char * s )
\brief Oøeže øetìzec o bílé znaky zleva.
\param s ukazatel na øetìzec
\return Ukazatel na novou pozici v tomtéž øetìzci
*/
char * RTrim( char * s );

/*! \fn char * LTrim( char * s )
\brief Oøeže øetìzec o bílé znaky zprava.
\param s ukazatel na øetìzec
\return Ukazatel na novou pozici v tomtéž øetìzci
*/
char * RTrim( char * s );

/*! \fn char * Trim( char * s )
\brief Oøeže øetìzec o bílé znaky z obou stran.
\param s ukazatel na øetìzec
\return Ukazatel na novou pozici v tomtéž øetìzci
*/
char * Trim( char *s );

#endif
