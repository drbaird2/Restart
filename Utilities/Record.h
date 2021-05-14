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

/*******************************************************************
 * Structure - Record
 * 
 * A structure used to hold the hit record for a single ray and keep
 * track of what was the most recent hit.
 * 
 * Variables
 * bool                     colided - True/False of a collision
 * shared_ptr<Material>     material_ptr - material of the collided object
 * Point3                   sceneHit - Point of colision
 * Normal                   sceneNormal - normal at point of colision
 * Ray                      sceneRay - the ray the colided
 * int                      depth - current depth of recursion 
 * Scene&                   sceneRef - reference to the actual scene
 * shared_ptr<Object>       lastObject - object that was collided with
 * double                   t - used for keeping track of a t minimum
 * double                   u - used for texture mapping
 * double                   v - used for texture mapping
 * Vec3                     lightDir - stored direction of light
 * Color                    col - color of the object (Unused)
 * Point3                   localHit - hit point in local space for texture mapping
 *******************************************************************/

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