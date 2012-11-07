#include "stdafx.h"

std::vector<Surface *> surfaces_;
std::vector<Material *> materials_;
std::vector<LightSource *> lightsources_;

Vector3 origin = Vector3(3,0,3);
Vector3 lookAt = Vector3(1.5f,0.0f,0);
Vector3 up = Vector3(0,0,1);
const float fov = 3.1415f / 3;
Cam* camera;
RayTracer* rt;

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
	
	//LoadOBJ( "../../data/test.obj", Vector3( 0.5f, 0.5f, 0.5f ), surfaces_, materials_ );
	
	Sphere* sp = new Sphere(Vector3(0,0,0), 1.0f, Color4(1,0,0,1));
	Surface* s = BuildSurfaceFromPrimitive("koule", sp);
	std::string name = "test";
	Material* test = new Material(name, Vector3(1.0f,0.0f,0.0f), Vector3(0.9f,0.1f,0.1f), Vector3(0.7f,0.1f,0.1f), 0.1f, 0.5f);
	s->set_material(test);
	surfaces_.push_back(s);

	sp = new Sphere(Vector3(2.3,0,0), 1.0f, Color4(0,1,0,1));
	s = BuildSurfaceFromPrimitive("koule2", sp);
	name = "test2";
	test = new Material(name, Vector3(1.0f,0.5f,1.0f), Vector3(0.5f,0.5f,0.5f), Vector3(0.5f,0.5f,0.5f), 0.2f, 0.5f);
	s->set_material(test);
	surfaces_.push_back(s);

	sp = new Sphere(Vector3(0,1,0), 1.0f, Color4(0,1,0,1));
	s = BuildSurfaceFromPrimitive("koule2", sp);
	name = "test2";
	test = new Material(name, Vector3(0.4f,1.0f,0.4f), Vector3(0.4f,1.0f,0.4f), Vector3(0.4f,1.0f,0.4f), 0.6f, 0.5f);
	s->set_material(test);
	surfaces_.push_back(s);

	sp = new Sphere(Vector3(0,0,1.3f), 0.2f, Color4(0,0,1,1));
	s = BuildSurfaceFromPrimitive("koule2", sp);
	name = "test2";
	test = new Material(name, Vector3(0.4f,1.0f,0.4f), Vector3(0.4f,1.0f,0.4f), Vector3(0.4f,1.0f,0.4f), 0.5f, 0.5f);
	s->set_material(test);
	surfaces_.push_back(s);

	LightSource* ls = new LightSource(Vector3(0,5.0f,5), 1.0f);
	lightsources_.push_back(ls);
	/*ls = new LightSource(Vector3(-5,-6,3), 1.0f);
	lightsources_.push_back(ls);*/

	camera = new Cam(origin, lookAt, up, fov);
	rt = new RayTracer(camera, lightsources_, surfaces_);

	// TODO: generování akcelerační struktury		

	float const antialiasingsize = 0.5f;

	double t0 = omp_get_wtime();
	for (int i = 0; i < IMG_SIZE; i++) {
		for (int j = 0; j < IMG_SIZE; j++) {
			float * pixel = MAT_ELEM(image, float, j, i);


			Color4 color;
			// anti-aliasing
			if(ANTIALIASING == 1) {
			Color4 c = Color4(0,0,0,1);
			int count = 0;
			for (float x =i- 0.5f; x <=i+0.5f; x+=antialiasingsize) {
				for (float y =j- 0.5f; y <=j+0.5f; y+=antialiasingsize) {
					c+= rt->GetResultColor(x,y);
					count++;
				}
			}
			color = Color4(c.r/(float) count,c.g/(float) count,c.b/(float) count,c.a/(float) count);
			} else {

			color = rt->GetResultColor(i,j);
			}
			pixel[0] = color.b;
			pixel[1] = color.g;
			pixel[2] = color.r;
			pixel[3] = color.a;
			
		}
		printf("ROW: %d \n", i+1);
	}

	cv::namedWindow( "Render", CV_WINDOW_AUTOSIZE );
	//cv::setWindowProperty("Render", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
	cv::imshow( "Render", image );	

	double t1 = omp_get_wtime();

	cv::waitKey( 0 );
	image.release();
	cv::destroyAllWindows();
	
	return 0;
}
