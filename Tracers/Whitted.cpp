// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Whitted.h"
#include "../Utilities/Scene.h"
#include "../Utilities/Record.h"
#include "../Materials/Material.h"

// -------------------------------------------------------------------- default constructor

Whitted::Whitted(void)
	: Tracer()
{}


// -------------------------------------------------------------------- constructor
		
Whitted::Whitted(Scene* sceneRef)
	: Tracer(sceneRef)
{}


// -------------------------------------------------------------------- destructor

Whitted::~Whitted(void) {}


// -------------------------------------------------------------------- trace_ray

Color Whitted::traceRay(const Ray& ra, const int depth) const {
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
