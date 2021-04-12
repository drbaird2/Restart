#ifndef PLANE_H
#define PLANE_H

#include "Object.h"
#include "../Utilities/Vec3.h"
#include "../Utilities/Ray.h"
#include "../Utilities/Record.h"
#include <memory>

class Plane : public Object{
    public:
        Point3 aPoint;
	    Normal theNormal;

	    Plane();
	    Plane(const Point3& point, const Normal& normal);
	    Plane(const Plane& plane);
	    Plane& operator=(const Plane& rhs);
	    virtual ~Plane();

	    virtual shared_ptr<Plane> clone() const;
	    virtual bool intersect(const Ray& ra, double& tMin,Record& recentHits);
};

#endif