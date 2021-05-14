

#include "Reflective.h"

// ---------------------------------------------------------------- default constructor

Reflective::Reflective (void)
	:	Phong(),
		reflective_brdf(new PerfectSpecular)
{}


// ---------------------------------------------------------------- copy constructor

Reflective::Reflective(const Reflective& rm)
	: 	Phong(rm) {
	
	if(rm.reflective_brdf)
		reflective_brdf = rm.reflective_brdf->clone(); 
	else  
		reflective_brdf = NULL;
}


// ---------------------------------------------------------------- assignment operator

Reflective& 
Reflective::operator= (const Reflective& rhs) {
	if (this == &rhs)
		return (*this);
		
	Phong::operator=(rhs);
	
	if (reflective_brdf) {
		reflective_brdf.reset();;
		reflective_brdf = NULL;
	}

	if (rhs.reflective_brdf)
		reflective_brdf = rhs.reflective_brdf->clone();

	return (*this);
}


// ---------------------------------------------------------------- clone

shared_ptr<Reflective> Reflective::clone(void) const {
	return (make_shared<Reflective>(*this));
}	


// ---------------------------------------------------------------- destructor

Reflective::~Reflective(void) {
	if (reflective_brdf) {
		reflective_brdf.reset();
		reflective_brdf = NULL;
	}
}


// ------------------------------------------------------------------------------------ shade 

Color Reflective::shade(Record& recentHits) {	
	Color L(Phong::shade(recentHits));  // direct illumination
	
	Vec3 wo = -recentHits.sceneRay.dir;
	Vec3 wi;	
	Color fr = reflective_brdf->sampleFunc(recentHits, wo, wi); 
	Ray reflected_ray(recentHits.sceneHit, wi); 
	//reflected_ray.depth = recentHits.depth + 1;
	
	L += fr * recentHits.sceneRef.tracerPtr->traceRay(reflected_ray, recentHits.depth + 1) * (recentHits.sceneNormal * wi);
					
	return (L);
}



