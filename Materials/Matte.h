#ifndef MATTE_H
#define MATTE_H

#include "Material.h"
#include "../BRDFs/Lambertian.h"
#include "../Utilities/Scene.h"


/*******************************************************************
 * Class - Matte
 * 
 * This is a matte material that has no specular component
 * 
 *******************************************************************/
class Matte : public Material{
    public:
        shared_ptr<Lambertian> ambientBRDF;
	    shared_ptr<Lambertian> diffuseBRDF;

	    Matte();
	    Matte(const Matte& m);
	    ~Matte();
	    Matte& operator=(const Matte& rhs);

	    shared_ptr<Matte> clone() const;

	    void setKa(const float k);
	    void setKd(const float k);
	    void setCd(const Color c);
	    void setCd(const double r, const double g, const double b);
	    void setCd(const float c);

	    void setSampler(shared_ptr<Sampler> sp);
	    void setSamples(const int numSamples);

	    Color shade(Record& recentHits) override;
	    Color pathShade(Record& recentHits) override;
	    Color globalShade(Record& recentHits) override;
	    Color areaLightShade(Record& recentHits) override;
	
};

#endif