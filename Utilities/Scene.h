#ifndef SCENE_H
#define SCENE_H


//Utilities
#include <vector>
#include <string>
#include <memory>
#include "Viewplane.h"
#include "Color.h"
#include "Record.h"


#include "../Tracers/Tracer.h"
#include "../Objects/Object.h"
//

#include "Ray.h"
#include "../Cameras/Camera.h"
#include "../Lights/Light.h"
#include "../Lights/Ambient.h"

using namespace std;
class Tracer;
class Camera;
class Record;
class Light;


class Scene{
    public:
	    Viewplane                   vp;
	    Color                       backgroundColor;
	    vector<shared_ptr<Object>>  objects;
	    shared_ptr<Tracer>          tracerPtr;
        shared_ptr<Camera>          cameraPtr;
		shared_ptr<Light> 			ambientPtr;
		vector<shared_ptr<Light>> 	lights;
        vector<Color>               pixels;
		int 						count;


	public:
        Scene();
	    ~Scene();
	
	    void build();
	    void renderScene();
	    void addObject(shared_ptr<Object> objects);
		void addLight(shared_ptr<Light> lightPtr);

	    Record intersect(const Ray& ray);
	    void DisplayPixel(const int row, const int column, const Color& pixelColor);
        void save_bmp(const string& outputFile) const;
        void setCamera(shared_ptr<Camera> camera);
		void setAmbientLight(shared_ptr<Light> light);
		AABB getBoundingBox();
};

inline void Scene::addObject(shared_ptr<Object> object_ptr) {  
	objects.push_back(object_ptr);	
}

inline void Scene::addLight(shared_ptr<Light> light_ptr) {  
	lights.push_back(light_ptr);	
}

#endif