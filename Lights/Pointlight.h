#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"
#include "../Utilities/Scene.h"

class PointLight : public Light{
    public:
        double ls;
	    Color col;
	    Vec3 location;

	    PointLight();
	    PointLight(const PointLight& pl);
	    ~PointLight();

	    PointLight& operator=(const PointLight& rhs);

	    shared_ptr<PointLight> clone() const;

	    void setScaleRadiance(const double b);
	    void setColor(const double c);
	    void setColor(const Color& c);
	    void setColor(const double r, const double g, const double b);
	    void setLocation(Vec3 d);
	    void setLocation(double dx, double dy, double dz);
	    Vec3 getDirection(Record& recentHits) override;
	    Color L(Record& recentHits) override;
	    bool inShadow(const Ray& ra, const Record& recentHits) const override;
	
};
#endif