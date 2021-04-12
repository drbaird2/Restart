
#include "Tracer.h"

// -------------------------------------------------------------------- default constructor

Tracer::Tracer()
	: scenePtr(NULL)
{}


// -------------------------------------------------------------------- constructor

Tracer::Tracer(Scene* scene_ref)
	: scenePtr(scene_ref)
{}


Tracer::~Tracer()
{}
// -------------------------------------------------------------------- trace_ray

Color Tracer::traceRay(const Ray& ra) const {
	return (black);
}

