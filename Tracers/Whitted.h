#ifndef WHITTED_H
#define WHITTED_H


// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Tracer.h"

class Whitted: public Tracer {
	public:
		
		Whitted(void);
		
		Whitted(Scene* sceneRef);
		
		virtual	~Whitted(void);
	
		Color traceRay(const Ray& ra, const int depth) const override;

		Color traceRay(const Ray& ray, double& tMin, const int depth) const override;


};

#endif
