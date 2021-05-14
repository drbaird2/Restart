#include "AreaLights.h"

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