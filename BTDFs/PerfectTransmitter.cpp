#include "PerfectTransmitter.h"

/*******************************************************************
 * Constructors
 * 
 *******************************************************************/

PerfectTransmitter::PerfectTransmitter(void)
	: 	BTDF(),
		kt(0.0), 
		ior(1.0)
{}


PerfectTransmitter::PerfectTransmitter(const PerfectTransmitter& pt)
	: 	BTDF(pt),
		kt(pt.kt), 
		ior(pt.ior)
{}


shared_ptr<PerfectTransmitter> PerfectTransmitter::clone(void) {
	return (make_shared< PerfectTransmitter>(*this));
}


PerfectTransmitter::~PerfectTransmitter(void) {}

/*******************************************************************
 * Assignment Operator
 *******************************************************************/
		
PerfectTransmitter&	PerfectTransmitter::operator= (const PerfectTransmitter& rhs) {
	if (this == &rhs)
		return (*this);
		
	kt = rhs.kt;
	ior = rhs.ior;

	return (*this);
}

/*******************************************************************
 * tir - Given a collison in a hit record, test if there is total
 * internal reflection
 * 
 *******************************************************************/

bool PerfectTransmitter::tir(const Record& recentHits) const {
	Vec3 wo(-recentHits.sceneRay.dir); 
	float cos_thetai = recentHits.sceneNormal * wo;  
	float eta = ior;
	
	if (cos_thetai < 0.0) 
		eta = 1.0 / eta; 
		
	return (1.0 - (1.0 - cos_thetai * cos_thetai) / (eta * eta) < 0.0);
}	


Color PerfectTransmitter::func(const Record& recentHits, const Vec3& wo, const Vec3& wi) const {
	return (black);
}


/*******************************************************************
 * SampleFunc
 * If there is no total internal reflection, checks if the ray is
 * in the object if it is reverse it and return the transmission
 * coefficient
 * 
 *******************************************************************/


Color PerfectTransmitter::sampleFunc(const Record& recentHits, const Vec3& wo, Vec3& wt) const {
	
	Normal n(recentHits.sceneNormal);
	float cos_thetai = n * wo;
	float eta = ior;	
		
	if (cos_thetai < 0.0) {			// transmitted ray is outside     
		cos_thetai = -cos_thetai;
		n = -n;  					// reverse direction of normal
		eta = 1.0 / eta; 			// invert ior 
	}

	float temp = 1.0 - (1.0 - cos_thetai * cos_thetai) / (eta * eta);
	float cos_theta2 = sqrt(temp);
	wt = -wo / eta - (cos_theta2 - cos_thetai / eta) * n;   
	
	return (kt / (eta * eta) * white / fabs(recentHits.sceneNormal * wt));
}

Color PerfectTransmitter::rho(const Record& recentHits, const Vec3& wo) const {
	return (black);
}


