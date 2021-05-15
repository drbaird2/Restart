#ifndef DIRECTIONAL_H
#define DIRECTIONAL_H

#include "Light.h"
#include "../Utilities/Scene.h"

/*******************************************************************
 * Class - Directional inherits from Light
 * 
 * a light from off screen that emits in a single direction
 * 
 * ls - Scale Radiance
 * Col - color of emitted light
 * Dir - direction of light
 * 
 *******************************************************************/
class Directional : public Light
{
public:
    double ls;
	Color col;
	Vec3 dir;

	Directional();
	Directional(const Directional& dl);
	~Directional();

	Directional& operator=(const Directional& rhs);

	shared_ptr<Directional> clone() const;

	void setScaleRadiance(const double b);
	void setColor(const double c);
	void setColor(const Color& c);
	void setColor(const double r, const double g, const double b);
	void setDirection(Vec3 d);
	void setDirection(double dx, double dy, double dz);
	
	Vec3 getDirection(Record& recentHits) override;
	Color L(Record& recentHits) override;
	bool inShadow(const Ray& ra, const Record& recentHits) const override;
	
};

#endif