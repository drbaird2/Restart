#include "Sphere.h"
#include "../Utilities/Constants.h"


Sphere::Sphere() :
    center(Point3(0,0,0)),
    radius(1.0)
{}

Sphere::Sphere(Point3 cen, double rad) :
    center(cen),
    radius(rad)
{}

Sphere::Sphere(const Sphere& sphere)
	: Object(sphere)
	, center(sphere.center)
	, radius(sphere.radius)
{
	mat = sphere.mat;
}

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
	auto a = ra.dir * ra.dir; // a = d * d
	auto b = 2.0 * oc*ra.dir; // b = 2(o - c) * d
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
			//recentHits.material_ptr = getMaterial();
			recentHits.lastObject = this->clone();
			return true;
		}

		t = (-b + sqrtd) / denom; //larger root
		if (t > kEpsilon)
		{
			tMin = t;
			recentHits.sceneNormal = (oc + t * ra.orig) / radius;
			recentHits.localHit = ra.orig + t * ra.dir;
			//recentHits.material_ptr = getMaterial();
			recentHits.lastObject = this->clone();
			return true;
		}
	}
	return false;
}

bool Sphere::shadowIntersect(const Ray& ra, double& tMin) const
{
	double t;
	Vec3 oc = ra.orig - center; //direction vector for Sphere. (o - c) 
	double a = ra.dir * ra.dir;  // a = d * d
	double b = 2.0 * oc * ra.dir; // b = 2(o - c) * d
	double c = oc.length_squared() - radius * radius; // c = (o - c) * (o - c) - r * r;
	double disc = b * b - 4.0 * a * c; // discriminant

	if (disc < 0.0) // No hit
	{
		return false;
	}
	else // one or two hit
	{
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom;  //swaller root

		if (t > kEpsilon)
		{
			tMin = t;
			return true;
		}

		t = (-b + e) / denom; //larger root
		if (t > kEpsilon)
		{
			tMin = t;
			return true;
		}
	}
	return false;
}

bool Sphere::getBoundingBox(AABB& outputBox) const
{
	Point3 p0(center.xPoint - radius, center.yPoint - radius, center.zPoint - radius);
	Point3 p1(center.xPoint + radius, center.yPoint + radius, center.zPoint + radius);
	outputBox = AABB(p0,p1);
//	std::cout << "Bound a sphere: " << this<< endl;
	return true;
}