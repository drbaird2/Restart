#ifndef PLANE_H
#define PLANE_H

#include "Object.h"
#include "../Utilities/Normal.h"
#include "../Utilities/Point3.h"
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
		bool shadowIntersect(const Ray& ray, double& tmin) const override;
		virtual bool getBoundingBox(AABB& outputBox) const;
};

#endif