#ifndef AREALIGHTS_H
#define AREALIGHTS_H

#include "Tracer.h"

/*******************************************************************
 * Class - AreaLights - inherits from Tracer
 * 
 * The tracer that is used to gather illumnation and make diffuse shadows
 * 
 *******************************************************************/

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