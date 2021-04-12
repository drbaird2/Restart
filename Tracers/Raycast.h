#ifndef RAYCAST_H
#define RAYCAST_H

#include "Tracer.h"

class Raycast : public Tracer
{
public:
	Raycast();
	Raycast(Scene* sceneRef);

	virtual ~Raycast();
	Color traceRay(const Ray& ra) const override;
};

#endif