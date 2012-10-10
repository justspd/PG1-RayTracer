#include "stdafx.h"


int main( int argc, char * argv[] )

	// TODO: Bilinearni interpolace - viz wiki - texture getTexel
	// TODO: Vyresit antialiasing

{
	printf( "PG1, (c)2011-2012 Tomas Fabian\n\n" );

	cv::namedWindow( "Render", CV_WINDOW_AUTOSIZE );
	cv::Mat image = cv::Mat( cv::Size( 640, 480 ), CV_32FC4, CV_RGB( 0, 0, 0 ) );
	cv::imshow( "Render", image );	

	float * pixel = MAT_ELEM(image, float, 10, 12);

	pixel[0] = 1.f;
	pixel[1] = 1.;
	pixel[2] = 0.5;
	pixel[3] = 1.;
	
	cv::imshow( "Render", image );	
	// TODO: vytvoření kamery
	
	// TODO: vytvoření světel		

	// načtení geometrie
	std::vector<Surface *> surfaces_;
	std::vector<Material *> materials_;
	LoadOBJ( "../../data/test.obj", Vector3( 0.5f, 0.5f, 0.5f ), surfaces_, materials_ );

	// TODO: generování akcelerační struktury		

	double t0 = omp_get_wtime();
	// TODO: ray tracing

	double t1 = omp_get_wtime();

	cv::waitKey( 0 );
	image.release();
	cv::destroyAllWindows();
	
	return 0;
}
