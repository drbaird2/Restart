#ifndef RAYCAST_H
#define RAYCAST_H

#include "Tracer.h"

/*******************************************************************
 * class - Raycast - inherits from Tracer, the main basic raycasting tracer
 * 
 * 
 *******************************************************************/
class Raycast : public Tracer
{
public:
	Raycast();
	Raycast(Scene* sceneRef);

	virtual ~Raycast();
	Color traceRay(const Ray& ra ,const int depth) const override;
};

#endif