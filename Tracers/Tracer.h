#ifndef TRACER_H
#define TRACER_H

#include "../Utilities/Constants.h"
#include "../Utilities/Ray.h"
#include "../Utilities/Color.h"
//#include "../Utilities/Scene.h"

class Scene;

class Tracer{
    public:
        Scene* scenePtr;
        Tracer();
        Tracer(Scene* scene_ref);
        virtual ~Tracer();

        virtual Color traceRay(const Ray& ra) const;
        virtual Color traceRay(const Ray& ra, const int depth) const;
        virtual Color traceRay(const Ray& ra, double& tMin, const int depth) const;

};


#endif