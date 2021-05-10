
#ifndef __AREA_LIGHT__
#define __AREA_LIGHT__

// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "../Utilities/Color.h"
#include "../Utilities/Vec3.h"
#include "Light.h"
#include "../Materials/Material.h"
#include "../Objects/Object.h"
#include "../Utilities/Scene.h"

class Arealight: public Light {	
	public:
	
		Arealight(void);						

		Arealight(const Arealight& al);				

		virtual shared_ptr<Arealight> clone(void);
		
		virtual ~Arealight(void);
		
		Arealight& operator= (const Arealight& rhs); 
		
		void setObject(shared_ptr<Object> objPtr);
		
		virtual Vec3 getDirection(Record& recentHits);
		
		virtual Color L(Record& recentHits);
		
		virtual bool inShadow(const Ray& ra, const Record& recentHits) const;
		
		virtual float G(Record& recentHits) ;
		
		virtual float pdf(Record& recentHits) const;
		
	public:
		
		shared_ptr<Object> 	        objectPtr;
		shared_ptr<Material>        materialPtr;	 // will be an emissive material
		Point3				        samplePoint;
		Normal				        lightNormal;    // assigned in get_direction - which therefore can't be const for any light
		Vec3			            wi;			     // unit direction from hit point being shaded to sample point on light surface			
	
};


// --------------------------------------------------------------- set_object

inline void Arealight::setObject(shared_ptr<Object> objPtr) {
	objectPtr = objPtr;
	materialPtr = objectPtr->getMaterial();	
}

#endif
