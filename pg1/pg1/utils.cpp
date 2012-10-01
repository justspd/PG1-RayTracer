#include "stdafx.h"

long long GetFileSize64( const char * file_name )
{
	FILE * file = fopen( file_name, "rb" );

	if ( file != NULL )
	{		
		_fseeki64( file, 0, SEEK_END ); // pøesun na konec souboru
		long long file_size = _ftelli64( file ); // zjištìní aktuální pozice
		_fseeki64( file, 0, SEEK_SET ); // pøesun zpìt na zaèátek
		fclose( file );
		file = NULL;

		return file_size;
	}

	return 0;	
}

char * LTrim( char * s )
{
    while ( isspace( *s ) || ( *s == 0 ) )
	{
		++s;
	};

    return s;
}

char * RTrim( char * s )
{
    char * back = s + strlen( s );

    while ( isspace( *--back ) );

    *( back + 1 ) = '\0';

    return s;
}

char * Trim( char * s )
{
	return RTrim( LTrim( s ) );
}
