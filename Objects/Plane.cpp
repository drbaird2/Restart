#include "Plane.h"
#include "../Utilities/Constants.h"

Plane::Plane():
    Object(),
	aPoint(0,0,0),
	theNormal(0, 1, 0)
{}

Plane::Plane(const Point3& point, const Normal& normal):
    Object(),
	aPoint(point),
	theNormal(normal)
{
	theNormal.unit_vector();
}

Plane::Plane(const Plane& plane):
	Object(),
	aPoint(plane.aPoint),
	theNormal(plane.theNormal)
{}

std::shared_ptr<Plane> Plane::clone() const{
	return make_shared<Plane>(*this);
}

Plane& Plane::operator=(const Plane& rhs){
	if (this == &rhs){
		return (*this);
	}

	Object::operator=(rhs);
	aPoint = rhs.aPoint;
	theNormal = rhs.theNormal;

	return (*this);
}

Plane::~Plane()
{}

bool Plane::intersect(const Ray& ra, double& tMin, Record& recentHits){
	auto denomenator = theNormal.dot(ra.dir);
    if(denomenator ==0){
        return false;
    }
	auto numerator = theNormal.dot((aPoint - ra.orig));
    double t = numerator/denomenator;
	if (t > kEpsilon)
	{
		tMin = t;
		recentHits.sceneNormal = theNormal;
		recentHits.localHit = ra.orig + t * ra.dir;

		return (true);
	}
	else
	{
		return (false);
	}
}