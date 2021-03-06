#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "BRDF.h"

/*******************************************************************
 * Class - Lambertian inherits from BRDF
 * 
 * The brdf for diffuse materials
 * 
 *******************************************************************/

class Lambertian : public BRDF{
    public:
        double kd;
	    Color cd;

	    Lambertian();
	    Lambertian(const Lambertian& lamb);
	    Lambertian& operator=(const Lambertian& rhs);
	    ~Lambertian();

	    shared_ptr<Lambertian> clone();

	    Color func(const Record& recentHits, const Vec3& wo, const Vec3& wi) const override;
	    virtual Color sampleFunc(const Record& recentHits, const Vec3& wo, Vec3& wi, float& pdf) const override;
	    virtual Color rho(const Record& recentHits, const Vec3& wo) const override;
	
	    void setKa(const double ka);
	    void setKd(const double kd);
	    void setCd(const Color& c);
	    void setCd(const double r, const double g, const double b);
	    void setCd(const double c);

		void setSampler(shared_ptr<Sampler> sp);
		void setSamples(const int numSamples);
	
};

#endif