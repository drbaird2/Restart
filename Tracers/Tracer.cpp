
#include "Tracer.h"

/*******************************************************************
 * Constructors
 * 
 *******************************************************************/

Tracer::Tracer()
	: scenePtr(NULL)
{}

Tracer::Tracer(Scene* scene_ref)
	: scenePtr(scene_ref)
{}


Tracer::~Tracer()
{}

/*******************************************************************
 * traceRay - The main function for all traces. comes in 3 versions
 * 
 * traceRay(Ray) - takes in a ray and returns black
 * 
 * traceRay(Ray,  int) - takes in a ray, and a current depth and returns black
 * 
 * traceRay(Ray, double, int) - takes in a ray, current depth, and 
 * 								the current minimum t and returns black
 *******************************************************************/

Color Tracer::traceRay(const Ray& ra) const {
	return (black);
}

Color Tracer::traceRay(const Ray& ray, const int depth) const
{
	return black;
}

Color Tracer::traceRay(const Ray& ray, double& tMin, const int depth) const
{
	return black;
}

