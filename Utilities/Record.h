#ifndef RECORD_H
#define RECORD_H

#include "Ray.h"
#include "Color.h"
//#include "Scene.h"
//#include "../Materials/Material.h"
#include <memory>

using namespace std;

class Scene;
class Material;

class Record{
    public:
        bool                    colided;
        shared_ptr<Material>    material_ptr;
        Point3                  sceneHit;
        Point3                  localHit;
        Normal                  sceneNormal;
        Color                   col;
        Ray                     sceneRay;
        Vec3                    lightDir;
        Scene&                  sceneRef;
        double                  t;
        double                  u;
        double                  v;

        Record(Scene& scene);
        Record(const Record& recentHits);
        ~Record();                 
};

#endif