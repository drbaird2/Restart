// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "Arealight.h"
#include "../Utilities/Constants.h"
#include <numeric>

// ---------------------------------------------------------------- default constructor
	
Arealight::Arealight(void): 	
        Light(),
		objectPtr(NULL),
		materialPtr(NULL)
{}	


// ---------------------------------------------------------------- copy constructor 
	
Arealight::Arealight(const Arealight& al)
	: 	Light(al) {
	if(al.objectPtr)
		objectPtr = al.objectPtr->clone(); 
	else  objectPtr = NULL;
	
	if(al.materialPtr){}
		//materialPtr = al.materialPtr->clone(); 
	else  materialPtr = NULL;
}


// ---------------------------------------------------------------- clone

shared_ptr<Arealight> Arealight::clone(void) {
	return make_shared<Arealight>(*this);
}					


// ---------------------------------------------------------------- destructor
 								
Arealight::~Arealight(void) {
	if (objectPtr) {
		objectPtr.reset();
		objectPtr = NULL;
	}
	
	if (materialPtr) {
		materialPtr.reset();
		materialPtr = NULL;
	}
}


// --------------------------------------------------------------- assignment operator

Arealight& Arealight::operator= (const Arealight& rhs) {
	if (this == &rhs)
		return (*this);

	if (rhs.objectPtr){
		objectPtr.reset();
		objectPtr = rhs.objectPtr;
	}



	if (rhs.materialPtr){
		materialPtr.reset();
		materialPtr = rhs.materialPtr;
	}
		

	return (*this);
}


// --------------------------------------------------------------- get_direction

Vec3 Arealight::getDirection(Record& recentHits) {
	samplePoint = objectPtr->sample();    // used in the G function
	lightNormal = objectPtr->getNormal(samplePoint); 
	wi = samplePoint - recentHits.sceneHit;  		// used in the G function
	wi.unit_vector();
	
	return (wi);
}


// --------------------------------------------------------------- L

Color Arealight::L(Record& recentHits) {
	float ndotd = -lightNormal*wi; 
	
	if (ndotd > 0.0)		
		return (materialPtr->getLe(recentHits)); 
	else
		return (black);
}


// ---------------------------------------------------------------- in_shadow	

bool Arealight::inShadow(const Ray& ra, const Record& recentHits) const {
	double t = kHugeValue;
	int num_objects = recentHits.sceneRef.objects.size();
	float ts = (samplePoint - ra.orig)*ra.dir;
	
	for (int j = 0; j < num_objects; j++){
		if (!recentHits.sceneRef.objects[j]->getIsShadow())
		{
			continue;
		}
		if (recentHits.sceneRef.objects[j]->shadowIntersect(ra, t) && t < ts){
			return (true); 
		}

	}
		
	return (false);     
}


// ---------------------------------------------------------------- G
// G is part of the geometric factor

float Arealight::G(const Record& recentHits)  {
	float ndotd = -lightNormal*wi;
	float d2 	= samplePoint.distance(recentHits.sceneHit)* samplePoint.distance(recentHits.sceneHit);
		
	return (ndotd / d2);
}


// ---------------------------------------------------------------- pdf

float Arealight::pdf(const Record& recentHits) const {
	return (objectPtr->pdf(recentHits));
}

