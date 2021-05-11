#ifndef AREALIGHTS_H
#define AREALIGHTS_H

#include "Tracer.h"

class AreaLights : public Tracer
{
public:
	AreaLights();
	AreaLights(Scene* scene);
	~AreaLights();
	Color traceRay(const Ray& ray, const int depth) const override;
	Color traceRay(const Ray& ray, double& tMin, const int depth) const override;
};

#endif