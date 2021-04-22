
//Utilities
#include "Constants.h"
#include "Vec3.h"
#include "Point2.h"
#include "Ray.h"
#include "Scene.h"

//Objects
#include "../Objects/Sphere.h"
#include "../Objects/Plane.h"
#include "../Objects/Triangle.h"

//Tracers
#include "../Tracers/Raycast.h"

//Camera
#include "../Cameras/Pinhole.h"
#include "../Cameras/Orthographic.h"

//Samplers
#include "../Samplers/Multijittered.h"

//Lights
#include "../Lights/Ambient.h"
#include "../Lights/Pointlight.h"
#include "../Lights/Directional.h"

//Materials
#include "../Materials/Matte.h"

//BRDFs
#include "../BRDFs/Lambertian.h"

Scene::Scene(): 
    backgroundColor(black),
	tracerPtr(nullptr),
	vp(),
	ambientPtr(nullptr),
	count(0)
{}

Scene::~Scene()
{
	tracerPtr.reset();
}

void Scene::build()
{
	vp.setHres(600);
	vp.setVres(300);
    vp.setPixelSize(1.0);
	int numSamples = 16;
	vp.setSamples(numSamples);
	vp.setSampler(move(make_shared<MultiJittered>(numSamples)));
	vp.setMaxDepth(10);
	backgroundColor = black;

	tracerPtr = make_shared<Raycast>(this);

	/* shared_ptr<Ambient> ambientPtr = make_shared<Ambient>();
	ambientPtr->setScaleRadiance(1.0);
	setAmbientLight(ambientPtr); */

	shared_ptr<Directional> flashlight = make_shared<Directional>();
	flashlight->setDirection(200, 250, 300);  
	flashlight->setColor(white);  			// for Figure 14.24(a)
	flashlight->setScaleRadiance(3.0);			
	//flashlight->set_shadows(true);    // see Chapter 16
	addLight(flashlight);

    shared_ptr<Pinhole> pinholePtr = make_shared<Pinhole>();
	pinholePtr->setEye(0, 25, 100);
	pinholePtr->setLookAt(0, 0, 0);
	pinholePtr->setViewDistance(6500);
	//pinholePtr->setZoom(1.0);
	pinholePtr->ComputeUVW();
	setCamera(pinholePtr);

    /* shared_ptr<Orthographic> orthoPtr = make_shared<Orthographic>();
	orthoPtr->setZWindow(100);
	setCamera(orthoPtr); */

	/* shared_ptr<PointLight> god = make_shared<PointLight>();
	god->setLocation(100,50,150);
	god->setScaleRadiance(3.0);
	addLight(god); */

	shared_ptr<PointLight> jesus = make_shared<PointLight>();
	jesus->setLocation(0,300,500);
	jesus->setScaleRadiance(3.0);
	addLight(jesus);

	shared_ptr<Matte> matteYellow = make_shared<Matte>();
	matteYellow->setKa(0.0);
	matteYellow->setKd(0.75);
	matteYellow->setCd(1,1,0);
	

	shared_ptr<Matte> matteOrange = make_shared<Matte>();
	matteOrange->setKa(0);
	matteOrange->setKd(0.75);
	matteOrange->setCd(1,0.5,0);

	shared_ptr<Matte> matteGreen = make_shared<Matte>();
	matteGreen->setKa(0);
	matteGreen->setKd(0.75);
	matteGreen->setCd(0,1,0);

	shared_ptr<Matte> matteRed = make_shared<Matte>();
	matteRed->setKa(0);
	matteRed->setKd(0.75);
	matteRed->setCd(solidred);

	double radius = 1.0;
	double gap = 0.2;

	shared_ptr<Sphere> sphere = make_shared<Sphere>();
	sphere->setCenter(-3.0 * radius - 1.5 * gap, 0.0, 0.0);
	sphere->setRadius(radius);
	sphere->setMaterial(matteRed);
	addObject(sphere);

	shared_ptr<Sphere> sphere2 = make_shared<Sphere>();
	sphere2->setCenter(-radius - 0.5 * gap, 0.0, 0.0);
	sphere2->setRadius(radius);
	sphere2->setMaterial(matteOrange);
	addObject(sphere2);

	shared_ptr<Sphere> sphere3 = make_shared<Sphere>();
	sphere3->setCenter(radius + 0.5 * gap, 0.0, 0.0);
	sphere3->setRadius(radius);
	sphere3->setMaterial(matteYellow);
	addObject(sphere3);

	shared_ptr<Sphere> sphere4 = make_shared<Sphere>();
	sphere4->setCenter(3.0 * radius + 1.5 * gap, 0.0, 0.0);
	sphere4->setRadius(radius);
	sphere4->setMaterial(matteGreen);
	addObject(sphere4);

	shared_ptr<Plane> plane = make_shared<Plane>();
	plane->aPoint = Point3(0,-1,0);
	plane->theNormal = Normal(0,1,0);
	plane->setMaterial(matteGreen);
	addObject(plane);

	/* shared_ptr<Sphere> sphere = make_shared<Sphere>();
	sphere->setCenter(0, 115, -1);
	sphere->setRadius(30);
	sphere->setMaterial(matteYellow);
	addObject(sphere);

	sphere.reset();
	sphere = make_shared<Sphere>();
	sphere->setCenter(0, 70, -1);
	sphere->setRadius(50);
	sphere->setMaterial(matteBlue);
	addObject(sphere);

	sphere.reset();
	sphere = make_shared<Sphere>();
	sphere->setCenter(0, 0, -1);
	sphere->setRadius(70);
	sphere->setMaterial(matteGreen);
	addObject(sphere); */


	/* shared_ptr<Plane> plane = make_shared<Plane>();
	plane->aPoint = Point3(0,-100,-1);
	plane->theNormal = Normal(0,-250,-1);
	plane->setMaterial(matteOrange);
	addObject(plane); */

	
}

void Scene::renderScene()
{
	Color pixelColor;
	Ray ra;
	double zw = 100.0;
	double x, y;
	
	
	ra.dir = Vec3(0, 0, -1);
	//cout << "P3\n" << vp.vres << " " << vp.hres << "\n255\n";
	for (int r = 0; r < vp.vres; r++) //up
	{
        cerr << "\rRendering: Row " << r << ' ' << std::flush;
		for (int c = 0; c < vp.hres; c++) //across
		{
			x = vp.pixelSize * (c - 0.5 * (vp.hres - 1.0));
			y = vp.pixelSize * (r - 0.5 * (vp.vres - 1.0));
			ra.orig = Point3(x, y, zw);
			pixelColor = tracerPtr->traceRay(ra);
			DisplayPixel(r, c, pixelColor);
		}
	}
}

Record Scene::intersect(const Ray& ra)
{
	Record recentHits(*this);
	double t;
	Normal norm;
	Point3 localHit;
	double tMin = kHugeValue;
	int numObjects = objects.size();

	for (int i = 0; i < numObjects; i++)
	{
		if (objects[i]->intersect(ra, t, recentHits) && (t < tMin))
		{
			recentHits.colided = true;
			tMin = t;
			recentHits.material_ptr = objects[i]->getMaterial();
			recentHits.sceneHit = ra.orig + t * ra.dir;
			norm = recentHits.sceneNormal;
			localHit = recentHits.localHit;
		}
	}

	if(recentHits.colided){
		recentHits.t = tMin;
		recentHits.sceneNormal = norm;
		recentHits.localHit = localHit;
	}

	return (recentHits);
}


void Scene::DisplayPixel(const int row, const int column, const Color& rawColor)
{
	Color mappedColor;

	//covert coordinate about y.
	/* int x = column;
	int y = vp.vres - row - 1; */

	int index = (column * vp.vres) + row;

	mappedColor.red = std::fmin(rawColor.red,1);
	mappedColor.green = std::fmin(rawColor.green,1);
	mappedColor.blue = std::fmin(rawColor.blue,1);

    pixels.push_back(mappedColor);

	cout << static_cast<int>(255.999 * mappedColor.red) << ' '
    << static_cast<int>(255.999 * mappedColor.green) << ' '
    << static_cast<int>(255.999 * mappedColor.blue) << '\n';

}

void Scene::save_bmp(const std::string& outputFile) const{
	const int image_size = vp.hres * vp.vres * 4;
    const int headers_size = 14 + 40;
    const int filesize = image_size + headers_size;
    const int pixelsPerMeter = 2835;
    
    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0};
    //size of the file in bytes
    bmpfileheader[ 2] = (unsigned char)(filesize);
    bmpfileheader[ 3] = (unsigned char)(filesize>>8);
    bmpfileheader[ 4] = (unsigned char)(filesize>>16);
    bmpfileheader[ 5] = (unsigned char)(filesize>>24);
            
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};
    //width of the image in bytes
    bmpinfoheader[ 4] = (unsigned char)(vp.hres);
    bmpinfoheader[ 5] = (unsigned char)(vp.hres>>8);
    bmpinfoheader[ 6] = (unsigned char)(vp.hres>>16);
    bmpinfoheader[ 7] = (unsigned char)(vp.hres>>24);
    
    //height of the image in bytes
    bmpinfoheader[ 8] = (unsigned char)(vp.vres);
    bmpinfoheader[ 9] = (unsigned char)(vp.vres>>8);
    bmpinfoheader[10] = (unsigned char)(vp.vres>>16);
    bmpinfoheader[11] = (unsigned char)(vp.vres>>24);

    // Size image in bytes
    bmpinfoheader[21] = (unsigned char)(image_size);
    bmpinfoheader[22] = (unsigned char)(image_size>>8);
    bmpinfoheader[23] = (unsigned char)(image_size>>16);
    bmpinfoheader[24] = (unsigned char)(image_size>>24);

    bmpinfoheader[25] = (unsigned char)(pixelsPerMeter);
    bmpinfoheader[26] = (unsigned char)(pixelsPerMeter>>8);
    bmpinfoheader[27] = (unsigned char)(pixelsPerMeter>>16);
    bmpinfoheader[28] = (unsigned char)(pixelsPerMeter>>24);

    bmpinfoheader[29] = (unsigned char)(pixelsPerMeter);
    bmpinfoheader[30] = (unsigned char)(pixelsPerMeter>>8);
    bmpinfoheader[31] = (unsigned char)(pixelsPerMeter>>16);
    bmpinfoheader[32] = (unsigned char)(pixelsPerMeter>>24);

    FILE *file = fopen(outputFile.c_str(), "wb");//write-binary
    
    fwrite(bmpfileheader,1,14, file);
    fwrite(bmpinfoheader,1,40, file);
    
    for (int i = 0; i < pixels.size(); ++i){
        const Color pixel = pixels[i];
        unsigned char color[3] = {
            static_cast<unsigned char> (pixel.blue * 255), 
            static_cast<unsigned char> (pixel.green * 255), 
            static_cast<unsigned char> (pixel.red * 255)
        };
        fwrite(color, 1, 3, file);
    }
    fclose(file);

}

void Scene::setCamera(shared_ptr<Camera> camera)
{
	if (cameraPtr)
	{
		cameraPtr.reset();
		cameraPtr = nullptr;
	}

	cameraPtr = camera;
}

void Scene::setAmbientLight(shared_ptr<Light> light)
{
	if (ambientPtr)
	{
		ambientPtr.reset();
		ambientPtr = nullptr;
	}

	ambientPtr = light;
}