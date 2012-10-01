/*! \file objloader.cpp
\brief Naèítání Wavefront OBJ souborù.
http://en.wikipedia.org/wiki/Wavefront_.obj_file
*/

#include "stdafx.h"

/*! \fn LoadMTL( const char * file_name, const char * path, std::vector<Material *> & materials )
\brief Naète materiály z MTL souboru \a file_name.
Soubor \a file_name se musí nacházet v cestì \a path. Naètené materiály budou vráceny pøes pole \a materials.
\param file_name název MTL souboru vèetnì pøípony.
\param path cesta k zadanému souboru.
\param materials pole materiálù, do kterého se budou ukládat naètené materiály.
*/
int LoadMTL( const char * file_name, const char * path, std::vector<Material *> & materials )
{
	// otevøení soouboru
	FILE * file = fopen( file_name, "rt" );
	if ( file == NULL )
	{
		printf( "File %s not found.\n", file_name );

		return -1;
	}

	// naètení celého souboru do pamìti
	/*const long long*/size_t file_size = static_cast<size_t>( GetFileSize64( file_name ) );
	char * buffer = new char[file_size + 1]; // +1 protože budeme za poslední naètený byte dávat NULL
	char * buffer_backup = new char[file_size + 1];	

	printf( "Loading materials from '%s' (%0.1f KB)...\n", file_name, file_size / 1024.0f );

	size_t number_of_items_read = fread( buffer, sizeof( *buffer ), file_size, file );

	// otestujeme korektnost naètení dat
	if ( !feof( file ) && ( number_of_items_read != file_size ) )
	{
		printf( "Unexpected end of file encountered.\n" );

		fclose( file );
		file = NULL;

		return -1;
	}	

	buffer[number_of_items_read] = 0; // zajistíme korektní ukonèení øetìzce

	fclose( file ); // ukonèíme práci se souborem
	file = NULL;

	memcpy( buffer_backup, buffer, file_size + 1 ); // záloha bufferu

	printf( "Done.\n\n");

	printf( "Parsing data...\n" );

	char material_name[128] = { 0 };
	char image_file_name[256] = { 0 };

	const char delim[] = "\n";
	char * line = strtok( buffer, delim );	

	Material * material = NULL;

	// --- naèítání všech materiálù ---
	while ( line != NULL )
	{
		if ( line[0] != '#' )
		{
			if ( strstr( line, "newmtl" ) == line )
			{
				if ( material != NULL )
				{
					material->set_name( material_name );
					materials.push_back( material );
				}
				material = NULL;

				sscanf( line, "%*s %s", &material_name );
				printf( "material name=%s\n", material_name );

				material = new Material();
			}
			else
			{
				char * tmp = Trim( line );				
				if ( strstr( tmp, "Ka" ) == tmp ) // ambient color of the material
				{
					sscanf( tmp, "%*s %f %f %f", &material->ambient.x, &material->ambient.y, &material->ambient.z );
				}
				if ( strstr( tmp, "Kd" ) == tmp ) // diffuse color of the material
				{
					sscanf( tmp, "%*s %f %f %f", &material->diffuse.x, &material->diffuse.y, &material->diffuse.z );
				}
				if ( strstr( tmp, "Ks" ) == tmp ) // specular color of the material
				{
					sscanf( tmp, "%*s %f %f %f", &material->specular.x, &material->specular.y, &material->specular.z );
				}
				if ( strstr( tmp, "Ns" ) == tmp ) // specular coefficient
				{
					sscanf( tmp, "%*s %f", &material->shininess );
				}
				if ( strstr( tmp, "map_Kd" ) == tmp ) // diffuse map
				{					
					sscanf( tmp, "%*s %s", image_file_name );
					Texture * texture = LoadTexture( std::string( path ).append( image_file_name ).c_str() );
					material->set_texture( 0, texture );
				}
			}
		}

		line = strtok( NULL, delim ); // naètení dalšího øádku
	}

	if ( material != NULL )
	{
		material->set_name( material_name );
		materials.push_back( material );
	}
	material = NULL;

	//memcpy( buffer, buffer_backup, file_size + 1 ); // obnovení bufferu po èinnosti strtok
	SAFE_DELETE_ARRAY( buffer_backup );
	SAFE_DELETE_ARRAY( buffer );	

	return 0;
}

int LoadOBJ( const char * file_name, Vector3 & default_color,
			std::vector<Surface *> & surfaces, std::vector<Material *> & materials )
{
	// otevøení soouboru
	FILE * file = fopen( file_name, "rt" );
	if ( file == NULL )
	{
		printf( "File %s not found.\n", file_name );

		return -1;
	}

	// cesta k zadanému souboru
	char path[128] = { "" };
	const char * tmp = strrchr( file_name, '/' );
	if ( tmp != NULL )
	{
		memcpy( path, file_name, sizeof( char ) * ( tmp - file_name + 1 ) );
	}

	// naètení celého souboru do pamìti
	/*const long long*/size_t file_size = static_cast<size_t>( GetFileSize64( file_name ) );
	char * buffer = new char[file_size + 1]; // +1 protože budeme za poslední naètený byte dávat NULL
	char * buffer_backup = new char[file_size + 1];	

	printf( "Loading mesh from '%s' (%0.1f MB)...\n", file_name, file_size / SQR( 1024.0f ) );

	size_t number_of_items_read = fread( buffer, sizeof( *buffer ), file_size, file );

	// otestujeme korektnost naètení dat
	if ( !feof( file ) && ( number_of_items_read != file_size ) )
	{
		printf( "Unexpected end of file encountered.\n" );

		fclose( file );
		file = NULL;

		return -1;
	}	

	buffer[number_of_items_read] = 0; // zajistíme korektní ukonèení øetìzce

	fclose( file ); // ukonèíme práci se souborem
	file = NULL;

	memcpy( buffer_backup, buffer, file_size + 1 ); // záloha bufferu

	printf( "Done.\n\n");

	printf( "Parsing data...\n" );

	char material_library[128] = { 0 };

	std::vector<std::string> material_libraries;	

	const char delim[] = "\n";
	char * line = strtok( buffer, delim );

	// --- naèítání všech materiálových knihoven, první prùchod ---
	while ( line != NULL )
	{
		switch ( line[0] )
		{	
		case 'm': // mtllib
			{
				sscanf( line, "%*s %s", &material_library );
				printf( "Material library: %s\n", material_library );				
				material_libraries.push_back( std::string( path ).append( std::string( material_library ) ) );
			}
			break;
		}

		line = strtok( NULL, delim ); // naètení dalšího øádku
	}

	memcpy( buffer, buffer_backup, file_size + 1 ); // obnovení bufferu po èinnosti strtok

	for ( int i = 0; i < static_cast<int>( material_libraries.size() ); ++i )
	{		
		LoadMTL( material_libraries[i].c_str(), path, materials );
	}

	std::vector<Vector3> vertices; // celý jeden soubor
	std::vector<Vector3> per_vertex_normals;
	std::vector<Vector2> texture_coords;	

	line = strtok( buffer, delim );	

	// --- naèítání všech souøadnic, druhý prùchod ---
	while ( line != NULL )
	{
		switch ( line[0] )
		{
		case 'v': // seznam vrcholù, normál nebo texturovacích souøadnic aktuální skupiny			
			{
				switch ( line[1] )
				{
				case ' ': // vertex
					{
						Vector3 vertex;
						sscanf( line, "%*s %f %f %f", &vertex.x, &vertex.y, &vertex.z );
						vertices.push_back( vertex );
					}
					break;

				case 'n': // normála vertexu
					{
						Vector3 normal;
						sscanf( line, "%*s %f %f %f", &normal.x, &normal.y, &normal.z );
						normal.Normalize();
						per_vertex_normals.push_back( normal );
					}
					break;

				case 't': // texturovací souøadnice
					{
						Vector2 texture_coord;
						TYPE_REAL z = 0;
						sscanf( line, "%*s %f %f %f",
							&texture_coord.x, &texture_coord.y, &z );					
						texture_coords.push_back( texture_coord );
					}
					break;
				}
			}
			break;		
		}

		line = strtok( NULL, delim ); // naètení dalšího øádku
	}

	memcpy( buffer, buffer_backup, file_size + 1 ); // obnovení bufferu po èinnosti strtok

	printf( "%d vertices, %d normals and %d texture coords.\n",
		vertices.size(), per_vertex_normals.size(), texture_coords.size() );

	/// buffery pro naèítání øetìzcù	
	char group_name[128];	
	char material_name[128];
	char vertices_indices[3][8 * 3 + 2];	// pomocný øetìzec pro naèítání indexù 3 x "v/vt/vn"
	char vertex_indices[3][8];				// pomocný øetìzec jednotlivých indexù "v", "vt" a "vn"	

	std::vector<Vertex> face_vertices; // pole všech vertexù právì naèítané face

	int no_surfaces = 0; // poèet naètených ploch

	line = strtok( buffer, delim ); // reset

	// --- naèítání jednotlivých objektù (group), tøetí prùchod ---
	while ( line != NULL )
	{
		switch ( line[0] )
		{
		case 'g': // group
			{
				if ( face_vertices.size() > 0 )
				{
					surfaces.push_back( BuildSurface( std::string( group_name ), face_vertices ) );
					++no_surfaces;
					face_vertices.clear();

					for ( int i = 0; i < static_cast<int>( materials.size() ); ++i )
					{
						if ( materials[i]->get_name().compare( material_name ) == 0 )
						{
							Surface * s = *--surfaces.end();
							s->set_material( materials[i] );
							break;
						}
					}
				}

				sscanf( line, "%*s %s", &group_name );
				printf( "Group name: %s\n", group_name );
			}
			break;

		case 'u': // usemtl			
			{
				sscanf( line, "%*s %s", &material_name );
				printf( "Material name: %s\n", material_name );						
			}
			break;

		case 'f': // face
			{
				// ! pøedpokládáme pouze trojúhelníky !
				// ! pøedpokládáme využití všech tøí položek v/vt/vn !				
				sscanf( line, "%*s %s %s %s",
					&vertices_indices[0], &vertices_indices[1], &vertices_indices[2] );				

				// TODO smoothing groups

				for ( int i = 0; i < 3; ++i )
				{
					sscanf( vertices_indices[i], "%[0-9]/%[0-9]/%[0-9]",
						&vertex_indices[0], &vertex_indices[1], &vertex_indices[2] );

					const int vertex_index = atoi( vertex_indices[0] ) - 1;
					const int texture_coord_index = atoi( vertex_indices[1] ) - 1;
					const int per_vertex_normal_index = atoi( vertex_indices[2] ) - 1;

					face_vertices.push_back( Vertex( vertices[vertex_index],
						per_vertex_normals[per_vertex_normal_index],
						default_color, &texture_coords[texture_coord_index] ) );
				}
			}
			break;
		}

		line = strtok( NULL, delim ); // naètení dalšího øádku
	}

	if ( face_vertices.size() > 0 )
	{
		surfaces.push_back( BuildSurface( std::string( group_name ), face_vertices ) );
		++no_surfaces;
		face_vertices.clear();

		for ( int i = 0; i < static_cast<int>( materials.size() ); ++i )
		{
			if ( materials[i]->get_name().compare( material_name ) == 0 )
			{
				Surface * s = *--surfaces.end();
				s->set_material( materials[i] );
				break;
			}
		}
	}

	texture_coords.clear();
	per_vertex_normals.clear();
	vertices.clear();	

	SAFE_DELETE_ARRAY( buffer_backup );
	SAFE_DELETE_ARRAY( buffer );	

	printf( "Done.\n\n");

	return no_surfaces;
}
