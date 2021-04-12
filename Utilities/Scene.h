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
//#include "light.h"
//#include "ambient.h"

using namespace std;
class Tracer;
class Camera;
class Record;

class Scene{
    public:
	    Viewplane                   vp;
	    Color                       backgroundColor;
	    vector<shared_ptr<Object>>  objects;
	    shared_ptr<Tracer>          tracerPtr;
        shared_ptr<Camera>          cameraPtr;
        vector<Color>               pixels;


	public:
        Scene();
	    ~Scene();
	
	    void build();
	    void renderScene();
	    void addObject(shared_ptr<Object> objects);
	    Record intersect(const Ray& ray);
	    void DisplayPixel(const int row, const int column, const Color& pixelColor);
        void save_bmp(const string& outputFile) const;
        void setCamera(shared_ptr<Camera> camera);
};

inline void Scene::addObject(shared_ptr<Object> object_ptr) {  
	objects.push_back(object_ptr);	
}


#endif