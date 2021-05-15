
#ifndef AREALIGHT_H
#define AREALIGHT_H

#include "Light.h"
#include "../Materials/Material.h"
#include "../Objects/Object.h"
#include "../Utilities/Scene.h"

/*******************************************************************
 * Class - Arealight inherits from Light
 * 
 * This is a object on the scene that has an emissive material and 
 * provides light in a localized area for softer shadows.
 * 
 * Variables
 * Objectptr - the object that becomes a light
 * materialptr - the emissive light material
 * 
 * 
 *******************************************************************/
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
		
		virtual bool inShadow(const Ray& ra, const Record& recentHits) const override;
		
		virtual float G(const Record& recentHits) override;
		
		virtual float pdf(const Record& recentHits) const override;
		
	public:
		
		shared_ptr<Object> 	        objectPtr;
		shared_ptr<Material>        materialPtr;	 // will be an emissive material
		Point3				        samplePoint;
		Normal				        lightNormal;    // assigned in get_direction - which therefore can't be const for any light
		Vec3			            wi;			     // unit direction from hit point being shaded to sample point on light surface			
	
};


inline void Arealight::setObject(shared_ptr<Object> objPtr) {
	objectPtr = objPtr;
	materialPtr = objectPtr->getMaterial();	
}

#endif
