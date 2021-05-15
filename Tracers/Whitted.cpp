#include "Whitted.h"
#include "../Utilities/Scene.h"
#include "../Utilities/Record.h"
#include "../Materials/Material.h"

/*******************************************************************
 * Constructors
 * 
 *******************************************************************/


Whitted::Whitted(void)
	: Tracer()
{}

		
Whitted::Whitted(Scene* sceneRef)
	: Tracer(sceneRef)
{}



Whitted::~Whitted(void) {}

/*******************************************************************
 * traceRay(Ray, Depth) - take a ray and a depth and return the 
 * 						color of the pixel
 * 
 *******************************************************************/

Color Whitted::traceRay(const Ray& ra, const int depth) const {

	//check if the depth is past the maximum allowed, if it is return black
	//else run a regular trace and update the depth.
	if (depth > scenePtr->vp.maxDepth)
		return(black);
	else {
		Record recentHits(scenePtr->intersect(ra));    
					
		if (recentHits.colided) {
			recentHits.depth = depth;
			recentHits.sceneRay = ra;	
			return (recentHits.material_ptr->shade(recentHits));   
		}
		else
			return (scenePtr->backgroundColor);
	}																																			
}

/*******************************************************************
 * traceRay(Ray, tmin, Depth) - take a ray, tmin, and depth and return the 
 * 						color of the pixel
 * Main difference from above is that we will also be updating the t 
 * with each collision.
 * 
 *******************************************************************/
Color Whitted::traceRay(const Ray& ray, double& tMin, const int depth) const
{
	if (depth > scenePtr->vp.maxDepth)
	{
		tMin = kHugeValue;
		return black;
	}
	else
	{
		Record recentHits(scenePtr->intersect(ray));
		if (recentHits.colided)
		{
			recentHits.depth = depth;
			recentHits.sceneRay = ray;
			tMin = recentHits.t;
			return recentHits.material_ptr->shade(recentHits);
		}
		else
		{
			tMin = kHugeValue;
			return scenePtr->backgroundColor;
		}
	}
}