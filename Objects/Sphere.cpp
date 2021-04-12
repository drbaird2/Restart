#include "Sphere.h"
#include "../Utilities/Constants.h"

Sphere::Sphere() :
    center(Point3(0,0,0)),
    radius(1.0)
{}

Sphere::Sphere(const Point3& cen, double rad) :
    center(cen),
    radius(rad)
{}

Sphere::~Sphere()
{}

shared_ptr<Sphere> Sphere::clone() const
{
	return make_shared<Sphere>((*this));
}

bool Sphere::intersect(const Ray& ra, double& tMin, Record& recentHits) 
{
	double t;
	Vec3 oc = ra.orig - center; //direction vector for Sphere. (o - c) 
	auto a = ra.dir.length_squared(); // a = d * d
	auto b = 2.0 * oc.dot(ra.dir); // b = 2(o - c) * d
	auto c = oc.length_squared() - radius * radius; // c = (o - c) * (o - c) - r * r;
	auto disc = b * b - 4.0 * a * c; // discriminant

	if (disc < 0.0) // No hit
	{
		return false;
	}
	else // one or two hit
	{
		double sqrtd = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - sqrtd) / denom;  //smaller root

		if (t > kEpsilon)
		{
			tMin = t;
			recentHits.sceneNormal = (oc + t * ra.dir) / radius; 
			recentHits.localHit = ra.orig + t * ra.dir;
			return true;
		}

		t = (-b + sqrtd) / denom; //larger root
		if (t > kEpsilon)
		{
			tMin = t;
			recentHits.sceneNormal = (oc + t * ra.orig) / radius;
			recentHits.localHit = ra.orig + t * ra.dir;
			return true;
		}
	}
	return false;
}