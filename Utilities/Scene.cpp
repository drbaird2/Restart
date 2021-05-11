
//Utilities
#include "Constants.h"
#include "Vec3.h"
#include "Point2.h"
#include "Ray.h"
#include "Scene.h"
#include <chrono>

//Objects
#include "../Objects/Sphere.h"
#include "../Objects/Plane.h"
#include "../Objects/Triangle.h"
#include "../Objects/AABB.h"
#include "../Objects/Rectangle.h"
#include "../Objects/BVH.h"
#include "../Objects/Obj.h"
#include "../Objects/Box.h"

//Tracers
#include "../Tracers/Raycast.h"
#include "../Tracers/Whitted.h"
#include "../Tracers/Arealights.h"

//Camera
#include "../Cameras/Pinhole.h"
#include "../Cameras/Orthographic.h"

//Samplers
#include "../Samplers/Multijittered.h"

//Lights
#include "../Lights/Ambient.h"
#include "../Lights/Pointlight.h"
#include "../Lights/Directional.h"
#include "../Lights/Arealight.h"

//Materials
#include "../Materials/Matte.h"
#include "../Materials/Emissive.h"
#include "../Materials/Phong.h"

//BRDFs
#include "../BRDFs/Lambertian.h"
#include "../BRDFs/GlossySpecular.h"



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
	int numSamples = 16;
	shared_ptr<MultiJittered> samp = make_shared<MultiJittered>(numSamples);
	vp.setHres(600);
	vp.setVres(600);
    vp.setPixelSize(1);
	vp.setSamples(numSamples);
	vp.setSampler(samp);
	vp.setMaxDepth(10);
	backgroundColor = Color(0.5);

	//tracerPtr = make_shared<Raycast>(this);
	tracerPtr = make_shared<AreaLights>(this);

	shared_ptr<Pinhole> pinholePtr = make_shared<Pinhole>();
	pinholePtr->setEye(-20, 10, 20);
	pinholePtr->setLookAt(0, 2, 0);
	pinholePtr->setViewDistance(1080);
	//pinholePtr->setZoom(1.0);
	pinholePtr->ComputeUVW();
	setCamera(pinholePtr);



	shared_ptr<Ambient> ambientPtr = make_shared<Ambient>();
	ambientPtr->setScaleRadiance(1.0);
	setAmbientLight(ambientPtr);

	shared_ptr<Directional> flashlight = make_shared<Directional>();
	flashlight->setDirection(0, 0, 0);  
//	flashlight->setColor(solidblue);  			
	flashlight->setScaleRadiance(4.0);			
	flashlight->setIsShadow(false);    
	addLight(flashlight);

    shared_ptr<Emissive> glow = make_shared<Emissive>();
	glow->setCe(white);
	glow->setLadiance(40.0);

	double width = 4;
	double height = 4;
	Point3 center(0.0, 7.0, -7.0);
	Point3 p0(-0.5 * width, center.yPoint - 0.5 * height, center.zPoint);
	Vec3 a(width, 0.0, 0.0);
	Vec3 b(0.0, height, 0.0);
	Normal norm(0, 0, 1);

	shared_ptr<Rectangle> rectang = make_shared<Rectangle>(p0,a,b,norm);
	rectang->setMaterial(glow);
	rectang->SetSampler(samp);
	rectang->setIsShadow(false);
	addObject(rectang);

	shared_ptr<Arealight> shield = make_shared<Arealight>();
	shield->setObject(rectang);
	shield->setIsShadow(true);
	addLight(shield);

	//addLight(shield);
	//addObject(shieldTri);

    /* shared_ptr<Orthographic> orthoPtr = make_shared<Orthographic>();
	orthoPtr->setZWindow(100);
	setCamera(orthoPtr); */

	/* shared_ptr<PointLight> god = make_shared<PointLight>();
	god->setLocation(100,50,150);
	god->setScaleRadiance(3.0);
	addLight(god);

	shared_ptr<PointLight> jesus = make_shared<PointLight>();
	jesus->setLocation(100,100,200);
	jesus->setScaleRadiance(3.0);
	jesus->setIsShadow(false);
	addLight(jesus); */

	shared_ptr<Matte> matteRed = make_shared<Matte>();
	matteRed->setKa(0.3);
	matteRed->setKd(0.3);
	matteRed->setCd(solidred);
	

	shared_ptr<Matte> matteBlue = make_shared<Matte>();
	matteBlue->setKa(0.1);
	matteBlue->setKd(0.90);
	matteBlue->setCd(solidblue);

	shared_ptr<Matte> matteGreen = make_shared<Matte>();
	matteGreen->setKa(0.1);
	matteGreen->setKd(0.2);
	matteGreen->setCd(solidgreen);

	/* double radi = 5;
	int ranMat, one, two, three;
	for(int i = 0; i<100; i++){
		shared_ptr<Sphere> sphere = make_shared<Sphere>();		
		ranMat = random_int(0,3);
		if(ranMat == 0){
			sphere->setMaterial(matteRed);
		}else if(ranMat == 1){
			sphere->setMaterial(matteGreen);
		}else{
			sphere->setMaterial(matteBlue);
		}
		sphere->setRadius(radi);
		one =  random_int(0,20);
		two = random_int(0,20);
		three = random_int(0,40);
		if(i%4 == 0){
			sphere->setCenter(Point3(one, two, -three));
		}else if(i%4 == 1){
			sphere->setCenter(Point3(-one, two, -three));
		}else if(i%4 == 2){
			sphere->setCenter(Point3(one, -two, -three));
		}else{
			sphere->setCenter(Point3(-one, -two, -three));
		}
		addObject(sphere);
	} */
	
	/* shared_ptr<Sphere> sphere = make_shared<Sphere>();
	sphere->setMaterial(matteBlue);
	sphere->setRadius(20);
	sphere->setCenter(Point3(45,-7,-30));
	addObject(sphere);

	shared_ptr<Sphere> sphere2 = make_shared<Sphere>();
	sphere2->setMaterial(matteRed);
	sphere2->setRadius(20);
	sphere2->setCenter(Point3(55,-14,-60));
	addObject(sphere2);

	shared_ptr<Rectangle> test = make_shared<Rectangle>();
	test->SetAB(Vec3(1,1,0),Vec3(-1,-1,0));
	test->SetP0(Point3(0,0,-30));
	test->setMaterial(matteBlue);
	addObject(test); */

	float box_width 	= 1.0; 		// x dimension
	float box_depth 	= 1.0; 		// z dimension
	float box_height 	= 4.5; 		// y dimension
	float gap			= 3.0; 

	shared_ptr<Box> box_ptr0 = make_shared<Box>(Point3(- 1.5 * gap - 2.0 * box_width, 0.0, -0.5 * box_depth), 
							Point3(-1.5 * gap  - box_width, box_height, 0.5 * box_depth)); 
	box_ptr0->setMaterial(matteGreen);
	addObject(box_ptr0);
	
	shared_ptr<Box> box_ptr1 = make_shared<Box>(Point3(- 0.5 * gap - box_width, 0.0, -0.5 * box_depth), 
							Point3(-0.5 * gap, box_height, 0.5 * box_depth)); 
	box_ptr1->setMaterial(matteGreen);
	addObject(box_ptr1);
		
	shared_ptr<Box> box_ptr2 = make_shared<Box>(Point3(0.5 * gap, 0.0, -0.5 * box_depth), 
							Point3(0.5 * gap + box_width, box_height, 0.5 * box_depth));
	box_ptr2->setMaterial(matteGreen);
	addObject(box_ptr2);
	
	shared_ptr<Box> box_ptr3 = make_shared<Box>(Point3(1.5 * gap + box_width, 0.0, -0.5 * box_depth), 
							Point3(1.5 * gap + 2.0 * box_width, box_height, 0.5 * box_depth));
	box_ptr3->setMaterial(matteGreen);
	addObject(box_ptr3);

		
	// ground plane
		
	/* shared_ptr<Plane> plane_ptr = make_shared<Plane>(Point3(0.0), Normal(0, 1, 0)); 
	plane_ptr->setMaterial(matteBlue);
	addObject(plane_ptr); */

//	sort(objects.begin()+0,objects.begin() + objects.size());

/* shared_ptr<Obj> cow = make_shared<Obj>("cow.obj");
cow->update_vertex_normals(matteBlue);
for(shared_ptr<Triangle> face:cow->getMeshes()){
	addObject(face);
} */
	/* shared_ptr<BVH> tree = make_shared<BVH>(*this);
	objects.clear();
	addObject(tree); */

}

/* void Scene::renderScene()
{
	Color pixelColor;
	Ray ra;
	double zw = 100.0;
	double x, y;
	
	
	ra.dir = Vec3(0, 0, -1);
	//cout << "P3\n" << vp.vres << " " << vp.hres << "\n255\n";
	std::chrono::steady_clock::time_point render_begin = std::chrono::steady_clock::now();
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
	std::chrono::steady_clock::time_point render_end = std::chrono::steady_clock::now();
    std::cout << "\nRender Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(render_end - render_begin).count() << "[ms]" << std::endl;
}
 */
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
			//recentHits.material_ptr = objects[i]->getMaterial();//recentHits.lastObject->getMaterial();
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

	/* cout << static_cast<int>(255.999 * mappedColor.red) << ' '
    << static_cast<int>(255.999 * mappedColor.green) << ' '
    << static_cast<int>(255.999 * mappedColor.blue) << '\n'; */

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

bool Scene::getBoundingBox(AABB& outputBox) const{
	if(objects.empty()){
		return false;
	}

	AABB tempBox;
	bool firstBox = true;

	for (const auto& object:objects){
		if (!object->getBoundingBox(tempBox)){
			return false;
		}
		
        outputBox = firstBox ? tempBox :  tempBox.surroundingBox(outputBox, tempBox);
        firstBox = false;
	}

	return true;
}
