  
#include "Raycast.h"
#include "../Utilities/Scene.h"
#include "../Utilities/Record.h"
#include "../Objects/Sphere.h"

Raycast::Raycast()
	: Tracer()
{

}

Raycast::Raycast(Scene* scene)
	: Tracer(scene)
{

}

Raycast::~Raycast()
{

}

Color Raycast::traceRay(const Ray& ra) const
{
	
	Record recentHits(scenePtr->intersect(ra));

	if (recentHits.colided)
	{
		return (recentHits.col);
	}
	else
	{
		return (scenePtr->backgroundColor);
	}
	
}