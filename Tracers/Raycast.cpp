  
#include "Raycast.h"
#include "../Utilities/Scene.h"
#include "../Utilities/Record.h"
#include "../Utilities/Ray.h"
#include "../Objects/Sphere.h"

/*******************************************************************
 * Constructors
 * 
 *******************************************************************/
Raycast::Raycast()
	: Tracer()
{}

Raycast::Raycast(Scene* scene)
	: Tracer(scene)
{

}

Raycast::~Raycast()
{

}

/*******************************************************************
 * traceRay(Ray, Depth) - the main function. Takes a Ray and the 
 * 							current depth and returns a color
 * 
 *******************************************************************/
Color Raycast::traceRay(const Ray& ra, const int depth) const
{

	//check and see if there was a collision and store it in the hit record
	Record recentHits(scenePtr->intersect(ra));		
	//if there is a collision return the color from the materials shade function. else return the background color
	if (recentHits.colided)
	{
		recentHits.sceneRay = ra;
		return recentHits.material_ptr->shade(recentHits);
	}
	else
	{
		return scenePtr->backgroundColor;
	}
}