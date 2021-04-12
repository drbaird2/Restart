
//Utilities
#include "Constants.h"
#include "Vec3.h"
#include "Point2.h"
#include "Ray.h"
#include "Scene.h"

//Objects
#include "../Objects/Sphere.h"

//Tracers
#include "../Tracers/Raycast.h"

//Camera
#include "../Cameras/Pinhole.h"
#include "../Cameras/Orthographic.h"

Scene::Scene(): 
    backgroundColor(black),
	tracerPtr(nullptr),
	vp()
{

}

Scene::~Scene()
{
	tracerPtr.reset();
}

void Scene::build()
{
	vp.setHres(500);
	vp.setVres(500);
    vp.setPixelSize(1.0);

	backgroundColor = black;

	tracerPtr = make_shared<Raycast>(this);

    shared_ptr<Pinhole> pinholePtr = make_shared<Pinhole>();
	pinholePtr->setEye(0, 100, -100);
	pinholePtr->setLookAt(0, -20, 0);
	pinholePtr->setViewDistance(1000);
	pinholePtr->setZoom(1.0);
	pinholePtr->ComputeUVW();
	setCamera(pinholePtr);

    /* shared_ptr<Orthographic> orthoPtr = make_shared<Orthographic>();
	orthoPtr->setZWindow(500);
	setCamera(orthoPtr); */


	shared_ptr<Sphere> sphere = make_shared<Sphere>();
	sphere->setCenter(0, 0, 0);
	sphere->setRadius(50);
	sphere->setColor(Color(1, 1, 0));
	addObject(sphere);

	sphere.reset();
	sphere = make_shared<Sphere>();
	sphere->setCenter(-40, -50, 0);
	sphere->setRadius(90);
	sphere->setColor(Color(0, 1, 0));
	addObject(sphere);

	sphere.reset();
	sphere = make_shared<Sphere>();
	sphere->setCenter(60, 130, 0);
	sphere->setRadius(70);
	sphere->setColor(Color(0, 1, 1));
	addObject(sphere);

	sphere.reset();
	sphere = make_shared<Sphere>(Point3(0, 30, 0), 60);
	sphere->setColor(Color(1, 1, 0));
	addObject(sphere);

	/* std::shared_ptr<Plane> plane = std::make_shared<Plane>(Point3D(0, 0, 0), Normal(0, 1, 1));
	plane->SetColor(RGBColor(0.3, 0.3, 0.3));
	AddObject(plane);  */
}

void Scene::renderScene()
{
	Color pixelColor;
	Ray ra;
	double zw = 100.0;
	double x, y;
	
	
	ra.dir = Vec3(0, 0, -1);

	for (int r = 0; r < vp.vres; r++) //up
	{
        std::cerr << "\rRendering: Row " << r << ' ' << std::flush;
		for (int c = 0; c <= vp.hres; c++) //across
		{
			x = vp.ps * (c - 0.5 * (vp.hres - 1.0));
			y = vp.ps * (r - 0.5 * (vp.vres - 1.0));
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
	double tMin = kHugeValue;
	int numObjects = objects.size();

	for (int i = 0; i < numObjects; i++)
	{
		if (objects[i]->intersect(ra, t, recentHits) && (t < tMin))
		{
			recentHits.colided = true;
			tMin = t;
			recentHits.col = objects[i]->getColor();
		}
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
    bmpinfoheader[ 4] = (unsigned char)(vp.vres);
    bmpinfoheader[ 5] = (unsigned char)(vp.vres>>8);
    bmpinfoheader[ 6] = (unsigned char)(vp.vres>>16);
    bmpinfoheader[ 7] = (unsigned char)(vp.vres>>24);
    
    //height of the image in bytes
    bmpinfoheader[ 8] = (unsigned char)(vp.hres);
    bmpinfoheader[ 9] = (unsigned char)(vp.hres>>8);
    bmpinfoheader[10] = (unsigned char)(vp.hres>>16);
    bmpinfoheader[11] = (unsigned char)(vp.hres>>24);

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