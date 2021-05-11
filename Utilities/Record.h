#ifndef RECORD_H
#define RECORD_H

#include "Ray.h"
#include "Color.h"
#include "Point3.h"
#include "Normal.h"
#include "../Objects/Object.h"
#include <memory>

using namespace std;

class Scene;
class Material;
class Object;

struct Record{
    public:
        bool                    colided;
        shared_ptr<Material>    material_ptr;
        Point3                  sceneHit;
        Normal                  sceneNormal;
        Ray                     sceneRay;
        int                     depth; 
        Scene&                  sceneRef;
        shared_ptr<Object>      lastObject;
        double                  t;
        double                  u;
        double                  v;
        Vec3                    lightDir;
        Color                   col;
        Point3                  localHit;
        Record(Scene& scene);
        Record(const Record& recentHits);
        ~Record();
};

#endif