#ifndef BRDF_H
#define BRDF_H

#include "../Utilities/Color.h"
#include "../Utilities/Vec3.h"
#include "../Utilities/Record.h"
#include "../Samplers/Sampler.h"


class BRDF{
    public:
        shared_ptr<Sampler> samplerPtr;
    
	    BRDF();
	    BRDF(const BRDF& brdf);
	    virtual shared_ptr<BRDF> clone() const = 0;
	    BRDF& operator=(const BRDF& rhs);
	    virtual ~BRDF();

	    void setSampler(shared_ptr<Sampler> sPtr);

	    virtual Color func(const Record& recentHits, const Vec3& wo, const Vec3& wi) const;
	    virtual Color sampleFunc(const Record& recentHits, const Vec3& wo, Vec3& wi) const;
	    virtual Color sampleFunc(const Record& recentHits, const Vec3& wo, Vec3& wi, float& pdf) const;
	    virtual Color rho(const Record& recentHits, const Vec3& wo) const;
};

#endif