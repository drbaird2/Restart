#include "PerfectTransmitter.h"

// ------------------------------------------------------------------- default constructor

PerfectTransmitter::PerfectTransmitter(void)
	: 	BTDF(),
		kt(0.0), 
		ior(1.0)
{}


// ------------------------------------------------------------------- copy constructor

PerfectTransmitter::PerfectTransmitter(const PerfectTransmitter& pt)
	: 	BTDF(pt),
		kt(pt.kt), 
		ior(pt.ior)
{}


// ------------------------------------------------------------------- clone

shared_ptr<PerfectTransmitter> PerfectTransmitter::clone(void) {
	return (make_shared< PerfectTransmitter>(*this));
}


// ------------------------------------------------------------------- destructor

PerfectTransmitter::~PerfectTransmitter(void) {}



// ------------------------------------------------------------------- assignment operator
		
PerfectTransmitter&	PerfectTransmitter::operator= (const PerfectTransmitter& rhs) {
	if (this == &rhs)
		return (*this);
		
	kt = rhs.kt;
	ior = rhs.ior;

	return (*this);
}


// ------------------------------------------------------------------- tir
// tests for total internal reflection

bool PerfectTransmitter::tir(const Record& recentHits) const {
	Vec3 wo(-recentHits.sceneRay.dir); 
	float cos_thetai = recentHits.sceneNormal * wo;  
	float eta = ior;
	
	if (cos_thetai < 0.0) 
		eta = 1.0 / eta; 
		
	return (1.0 - (1.0 - cos_thetai * cos_thetai) / (eta * eta) < 0.0);
}	


// ------------------------------------------------------------------- f

Color PerfectTransmitter::func(const Record& recentHits, const Vec3& wo, const Vec3& wi) const {
	return (black);
}


// ------------------------------------------------------------------- sample_f
// this computes the direction wt for perfect transmission
// and returns the transmission coefficient
// this is only called when there is no total internal reflection

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


// ------------------------------------------------------------------- rho

Color PerfectTransmitter::rho(const Record& recentHits, const Vec3& wo) const {
	return (black);
}


