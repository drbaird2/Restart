#ifndef BRDF_H
#define BRDF_H

#include "../Utilities/Color.h"
#include "../Utilities/Vec3.h"
#include "../Utilities/Record.h"
#include "../Samplers/Sampler.h"

/*******************************************************************
 * Class BRDF
 * 
 * Base class of all Bidirectional reflectance distribution functions
 * Defines light for opaque surfaces
 * 
 * Variables
 * 
 * shared_Ptr<Sampler> samplerptr - pointer to the sampler
 * 
 * 
 *******************************************************************/
class BRDF{
    public:
        shared_ptr<Sampler> samplerPtr;
    
	    BRDF();
	    BRDF(const BRDF& brdf);
	    shared_ptr<BRDF> clone();
	    BRDF& operator=(const BRDF& rhs);
	    virtual ~BRDF();

	    void setSampler(shared_ptr<Sampler> sPtr);

	    virtual Color func(const Record& recentHits, const Vec3& wo, const Vec3& wi) const;
	    virtual Color sampleFunc(const Record& recentHits, const Vec3& wo, Vec3& wi) const;
	    virtual Color sampleFunc(const Record& recentHits, const Vec3& wo, Vec3& wi, float& pdf) const;
	    virtual Color rho(const Record& recentHits, const Vec3& wo) const;
};

#endif