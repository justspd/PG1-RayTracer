#include "stdafx.h"

std::vector<Surface *> surfaces_;
std::vector<Material *> materials_;
std::vector<LightSource *> lightsources_;

Vector3 origin = Vector3(3.0f,1.0f,0);
Vector3 lookAt = Vector3(0.0f,0.0f,-1);
Vector3 up = Vector3(1,0,0);
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

	Texture* t = LoadTexture("../../data/box.jpg");

	camera = new Cam(origin, lookAt, up, fov);
	
	Sphere* sp = new Sphere(Vector3(0,0,-5), 2.0f, Vector3(0,0,1), t);
	Surface* s = BuildSurfaceFromPrimitive("koule", sp);
	std::string name = "test";
	Material* test = new Material(name, Vector3(0.0f,0.0f,0.0f), Vector3(0.0f,1.0f,0.0f), Vector3(0.9f,0.9f,0.9f), 1.0f, IOR_AIR,0.0f);
	s->set_material(test);
	surfaces_.push_back(s);

	sp = new Sphere(Vector3(0.6f,0,-1), 1.0f, Vector3(0,0,1));
	s = BuildSurfaceFromPrimitive("koule2", sp);
	name = "test2";
	test = new Material(name, Vector3(0.0f,1.0f,0.0f), Vector3(0.0f,0.0f,1.0f), Vector3(1.0f,0.0f,0.0f), 0.3, IOR_AIR, 0.0f);
	s->set_material(test);
	surfaces_.push_back(s);

	/*Block* b = new Block(Vector3(-0.3,-0.3,-0.3), Vector3(0.0,0.0,0.0));
	Surface* s2 = BuildSurfaceFromPrimitive("block", b);
	std::string name2 = "test";
	Material* test2 = new Material(name2, Vector3(1.0f,1.0f,1.0f), Vector3(1.0f,0.0f,0.0f), Vector3(1.0f,0.0f,0.0f), 0.0, IOR_AIR, 0.0);
	s2->set_material(test2);
	surfaces_.push_back(s2);*/

	

	/*sp = new Sphere(Vector3(4,0,0), 0.2f, Vector3(0,0,1));
	s = BuildSurfaceFromPrimitive("koule2", sp);
	name = "test2";
	test = new Material(name, Vector3(0.4f,1.0f,0.4f), Vector3(0.4f,1.0f,0.4f), Vector3(0.4f,1.0f,0.4f), 1.0f,  IOR_AIR, 0.0f);
	s->set_material(test);
	surfaces_.push_back(s);*/

	LightSource* ls = new LightSource(Vector3(4,0.0,0.0), 1.0f);
	lightsources_.push_back(ls);
	/*ls = new LightSource(Vector3(-5,-6,3), 1.0f);
	lightsources_.push_back(ls);*/

	std::vector<Texture*> env_tex(SIDE_COUNT);
	
	env_tex[SIDE_POSX] = LoadTexture("../../data/env2/posx.jpg");
	env_tex[SIDE_NEGX] = LoadTexture("../../data/env2/negx.jpg");
	env_tex[SIDE_POSY] = LoadTexture("../../data/env2/posy.jpg");
	env_tex[SIDE_NEGY] = LoadTexture("../../data/env2/negy.jpg");
	env_tex[SIDE_POSZ] = LoadTexture("../../data/env2/posz.jpg");
	env_tex[SIDE_NEGZ] = LoadTexture("../../data/env2/negz.jpg");
	EnvironmentSphere* env = new EnvironmentSphere(Vector3(0,0,0), Vector3(0,0,1), 10.0, env_tex);

	rt = new RayTracer(camera, lightsources_, surfaces_, env);

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
