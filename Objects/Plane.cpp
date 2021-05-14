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
	theNormal.normalize();
}

Plane::Plane(const Plane& plane):
	Object(),
	aPoint(plane.aPoint),
	theNormal(plane.theNormal)
{
	mat = plane.mat;
}

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
	auto denomenator = ra.dir * theNormal;
    if(denomenator == 0){
        return false;
    }
	auto numerator = (aPoint - ra.orig)*theNormal;
    double t = numerator/denomenator;
	if (t > kEpsilon)
	{
		tMin = t;
		recentHits.sceneNormal = theNormal;
		recentHits.localHit = ra.orig + t * ra.dir;
		//recentHits.material_ptr = getMaterial();
		recentHits.lastObject = this->clone();

		return (true);
	}
	else
	{
		return (false);
	}
}

bool Plane::shadowIntersect(const Ray& ra, double& tMin) const
{
	double t = (aPoint - ra.orig)*theNormal / (ra.dir*theNormal);

	if (t > kEpsilon)
	{
		tMin = t;
		return (true);
	}
	else
	{
		return false;
	}
}

bool Plane::getBoundingBox(AABB& outputBox) const{
	return false;
}