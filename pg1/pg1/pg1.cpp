#include "stdafx.h"

std::vector<Surface *> surfaces_;
std::vector<Material *> materials_;
std::vector<LightSource *> lightsources_;

Vector3 origin = Vector3(1,1,3);
Vector3 lookAt = Vector3(-0.5f,0.0f,0);
Vector3 up = Vector3(0,0,1);
const float fov = 3.1415f / 3;
Cam* camera;
RayTracer* rt;

Color4 RayTrace(Ray * ray) {
	int size = surfaces_.size();
	for (int i = 0; i < size; i++) {
		Surface* actual = surfaces_.at(i);
		int triangle_count = actual->no_triangles();
		for (int j = 0; j < triangle_count; j++) {
			float t = 0;
			if( actual->get_triangles()[j].Intersect(ray, &t) == HIT) {
				return Color4(1,0,0,1);
			}
		}
	}
	return Color4(0,0,0,1);
}

int main( int argc, char * argv[] )

	// TODO: Bilinearni interpolace (wiki) - texture getTexel
	// TODO: Vyresit antialiasing
	// TODO: Fresnel equations (wiki)
	// TODO: Snells law (wiki)

{
	printf( "PG1, (c)2011-2012 Tomas Fabian\n\n" );

	//cv::namedWindow( "Render", CV_WINDOW_NORMAL );
	//cv::setWindowProperty("Render", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
	cv::Mat image = cv::Mat( cv::Size( IMG_SIZE, IMG_SIZE ), CV_32FC4, CV_RGB( 0, 0, 0 ) );
	//cv::imshow( "Render", image );

	// načtení geometrie
	
	LoadOBJ( "../../data/test.obj", Vector3( 0.5f, 0.5f, 0.5f ), surfaces_, materials_ );

	LightSource* ls = new LightSource(Vector3(10,10,10));
	lightsources_.push_back(ls);

	camera = new Cam(origin, lookAt, up, fov);
	rt = new RayTracer(camera, lightsources_, surfaces_);

	// TODO: generování akcelerační struktury		

	float const antialiasingsize = 0.5f;

	double t0 = omp_get_wtime();
	// TODO: ray tracing
	for (int i = 0; i < IMG_SIZE; i++) {
		for (int j = 0; j < IMG_SIZE; j++) {
			float * pixel = MAT_ELEM(image, float, j, i);


			// anti-aliasing
			Color4 c = Color4(0,0,0,1);
			int count = 0;
			for (float x =i- 0.5f; x <=i+0.5f; x+=antialiasingsize) {
				for (float y =j- 0.5f; y <=j+0.5f; y+=antialiasingsize) {
					c+= rt->GetResultColor(x,y);
					count++;
				}
			}
			Color4 color = Color4(c.r/(float) count,c.g/(float) count,c.b/(float) count,c.a/(float) count);
			pixel[0] = color.b;
			pixel[1] = color.g;
			pixel[2] = color.r;
			pixel[3] = color.a;
			
		}
		printf("ROW: %d \n", i+1);
	}

	cv::namedWindow( "Render", CV_WINDOW_NORMAL );
	cv::setWindowProperty("Render", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
	cv::imshow( "Render", image );	

	double t1 = omp_get_wtime();

	cv::waitKey( 0 );
	image.release();
	cv::destroyAllWindows();
	
	return 0;
}
