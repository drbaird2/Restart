#include "PerfectSpecular.h"
#include "../Utilities/Constants.h"

// ---------------------------------------------------------- default constructor

PerfectSpecular::PerfectSpecular(void)
	: 	BRDF(),
		kr(0.0), 
		cr(1.0)
{}

// ---------------------------------------------------------- destructor

PerfectSpecular::~PerfectSpecular(void) {}


// ---------------------------------------------------------------------- clone

shared_ptr<PerfectSpecular> PerfectSpecular::clone(void) const {
	return (make_shared<PerfectSpecular>(*this));
}	


// ---------------------------------------------------------- f

Color PerfectSpecular::func(const Record& recentHits, const Vec3& wo, const Vec3& wi) const {
	return (black);
}


// ---------------------------------------------------------- sample_f
// this computes wi: the direction of perfect mirror reflection
// it's called from from the functions Reflective::shade and Transparent::shade.
// the fabs in the last statement is for transparency

Color PerfectSpecular::sampleFunc(const Record& recentHits, const Vec3& wo, Vec3& wi) const {
	float ndotwo = recentHits.sceneNormal * wo;
	wi = -wo + 2.0 * recentHits.sceneNormal * ndotwo; 
	return (kr * cr / fabs(recentHits.sceneNormal * wi)); // why is this fabs? // kr would be a Fresnel term in a Fresnel reflector
}											 // for transparency when ray hits inside surface?, if so it should go in Chapter 24


// ---------------------------------------------------------- sample_f
// this version of sample_f is used with path tracing
// it returns ndotwi in the pdf

Color PerfectSpecular::sampleFunc(const Record& recentHits, const Vec3& wo, Vec3& wi, float& pdf) const {
	float ndotwo = recentHits.sceneNormal * wo;
	wi = -wo + 2.0 * recentHits.sceneNormal * ndotwo; 
	pdf = fabs(recentHits.sceneNormal * wi);
	return (kr * cr);  
}

// ---------------------------------------------------------- rho

Color PerfectSpecular::rho(const Record& recentHits, const Vec3& wo) const {
	return (black);
}

