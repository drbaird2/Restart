#include "AreaLights.h"


/*******************************************************************
 * Constructors
 * 
 *******************************************************************/

AreaLights::AreaLights()
	: Tracer()
{
}

AreaLights::AreaLights(Scene* scene)
	: Tracer(scene)
{
}

AreaLights::~AreaLights()
{
}

/*******************************************************************
 * traceRay(Ray, Depth) - take a ray and a depth and return the 
 * 						color of the pixel. in particular we will be 
 * 						using the arealight version of the materials 
 * 						shade function
 * 
 *******************************************************************/

Color AreaLights::traceRay(const Ray& ray, const int depth) const
{
	if (depth > scenePtr->vp.maxDepth)
	{
		return black;
	}
	else
	{

		Record recentHits(scenePtr->intersect(ray)); 

		if (recentHits.colided)
		{
			recentHits.sceneRay = ray;
			recentHits.depth = depth;

			return recentHits.material_ptr->areaLightShade(recentHits);
		}
		else
		{
			return scenePtr->backgroundColor;
		}
	}
}

/*******************************************************************
 * traceRay(Ray, Depth) - take a ray and a depth and return the 
 * 						color of the pixel. in particular we will be 
 * 						using the arealight version of the materials 
 * 						shade function. Also keeps track of the 
 * 						closest t value.
 * 
 *******************************************************************/
Color AreaLights::traceRay(const Ray& ray, double& tMin, const int depth) const
{
	if (depth > scenePtr->vp.maxDepth)
	{
		tMin = kHugeValue;
		return black;
	}
	else
	{

		Record recentHits(scenePtr->intersect(ray)); //for multi thread

		if (recentHits.colided)
		{
			recentHits.sceneRay = ray;
			recentHits.depth = depth;
			tMin = recentHits.t;
			return recentHits.material_ptr->areaLightShade(recentHits);
		}
		else
		{
			tMin = kHugeValue;
			return scenePtr->backgroundColor;
		}
	}
}