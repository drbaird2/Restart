#include "PerfectSpecular.h"
#include "../Utilities/Constants.h"



PerfectSpecular::PerfectSpecular(void)
	: 	BRDF(),
		kr(0.0), 
		cr(1.0)
{}



PerfectSpecular::~PerfectSpecular(void) {}




shared_ptr<PerfectSpecular> PerfectSpecular::clone(void) const {
	return (make_shared<PerfectSpecular>(*this));
}	




Color PerfectSpecular::func(const Record& recentHits, const Vec3& wo, const Vec3& wi) const {
	return (black);
}

/*******************************************************************
 * sampleFunc - computes the direction of the reflection - wi
 * 
 *******************************************************************/


Color PerfectSpecular::sampleFunc(const Record& recentHits, const Vec3& wo, Vec3& wi) const {
	float ndotwo = recentHits.sceneNormal * wo;
	wi = -wo + 2.0 * recentHits.sceneNormal * ndotwo; 
	return (kr * cr / fabs(recentHits.sceneNormal * wi)); 
}											


/*******************************************************************
 * Sample function used for Path Tracing (not Implemented)
 * 
 *******************************************************************/

Color PerfectSpecular::sampleFunc(const Record& recentHits, const Vec3& wo, Vec3& wi, float& pdf) const {
	float ndotwo = recentHits.sceneNormal * wo;
	wi = -wo + 2.0 * recentHits.sceneNormal * ndotwo; 
	pdf = fabs(recentHits.sceneNormal * wi);
	return (kr * cr);  
}

Color PerfectSpecular::rho(const Record& recentHits, const Vec3& wo) const {
	return (black);
}

