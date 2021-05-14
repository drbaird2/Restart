
#include "BTDF.h"

// ------------------------------------------------------------------------ default constructor

BTDF::BTDF(void) {}


// ------------------------------------------------------------------------ copy constructor

BTDF::BTDF(const BTDF& btdf) {}


// ------------------------------------------------------------------------ destructor

BTDF::~BTDF(void) {}

shared_ptr<BTDF> BTDF::clone(void){
	return make_shared<BTDF>(*this);
}


// ------------------------------------------------------------------------ assignment operator

BTDF& BTDF::operator= (const BTDF& rhs) {
	if (this == &rhs)
		return (*this);

	return (*this);
}


// ------------------------------------------------------------------------ f

Color BTDF::func(const Record& recentHits, const Vec3& wo, const Vec3& wi) const {
	return (black);
}


// ------------------------------------------------------------------------ sample_f
Color BTDF::sampleFunc(const  Record& recentHits, const Vec3& wo, Vec3& wi) const {
	return (black);
}


// ------------------------------------------------------------------------ rho	
	
Color BTDF::rho(const  Record& recentHits, const Vec3& wo) const {
	return (black);
}
