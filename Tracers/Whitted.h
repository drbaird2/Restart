#ifndef WHITTED_H
#define WHITTED_H

#include "Tracer.h"

/*******************************************************************
 * class - Whitted - inherits from Tracer
 * 
 * Main use is to recursively perform raytraces to simulate 
 * refraction and reflection
 * 
 *******************************************************************/
class Whitted: public Tracer {
	public:
		
		Whitted(void);
		
		Whitted(Scene* sceneRef);
		
		virtual	~Whitted(void);
	
		Color traceRay(const Ray& ra, const int depth) const override;

		Color traceRay(const Ray& ray, double& tMin, const int depth) const override;


};

#endif
