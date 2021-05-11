#include "Triangle.h"
#include "../Utilities/Constants.h"
#include <algorithm>

Triangle::Triangle():
	Object(),
	v0(0,0,0),
	v1(0,0,1),
	v2(1,0,0),
	norm(0,1,0)
{
	n0 = n1 = n2 = norm;
}

Triangle::Triangle(const Point3& a, const Point3& b, const Point3& c):
	Object(),
	v0(a),
	v1(b),
	v2(c)
{
	norm = (v1 - v0) ^ (v2 - v0);
	norm.normalize();
	n0 = n1 = n2 = norm;
}

Triangle::Triangle(const Triangle& triangle):
	Object(triangle),
	v0(triangle.v0),
	v1(triangle.v1),
	v2(triangle.v2),
	norm(triangle.norm),
	n0(triangle.n0),
	n1(triangle.n1),
	n2(triangle.n2)
{}

Triangle::~Triangle()
{}

Triangle& Triangle::operator=(const Triangle& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	v0 = rhs.v0;
	v1 = rhs.v1;
	v2 = rhs.v2;
	norm = rhs.norm;
	n0 = rhs.n0;
	n1 = rhs.n1;
	n2 = rhs.n2;
	return *this;
}


bool Triangle::intersect(const Ray& ra, double& tMin, Record& recentHits)
{
	double a = v0.xPoint - v1.xPoint;
    double b = v0.xPoint - v2.xPoint;
	double c = ra.dir.xPoint;
    double d = v0.xPoint - ra.orig.xPoint;
	double e = v0.yPoint - v1.yPoint;
    double f = v0.yPoint - v2.yPoint;
	double g = ra.dir.yPoint;
    double h = v0.yPoint - ra.orig.yPoint;
	double i = v0.zPoint - v1.zPoint;
    double j = v0.zPoint - v2.zPoint;
	double k = ra.dir.zPoint, l = v0.zPoint - ra.orig.zPoint;
	
	double m = f * k - g * j, n = h * k - g * l;
	double p = f * l - h * j, q = g * i - e * k;
	double s = e * j - f * i;

	double invDenom = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * invDenom;

	// first check
	if (beta < 0.0)
	{
		return false;
	}

	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * invDenom;

	// second check
	if (gamma < 0.0)
	{
		return false;
	}

	// third check
	if (beta + gamma > 1.0)
	{
		return false;
	}

	double e3 = a * p - b * r + d * s;
	double t = e3 * invDenom;

	// final check
	if (t < kEpsilon)
	{
		return false;
	}

	//hit
	tMin = t;
	recentHits.sceneNormal = norm;
	recentHits.localHit = ra.orig + t * ra.dir;
    recentHits.material_ptr = getMaterial();

	return true;
}

 bool Triangle::shadowIntersect(const Ray& ra, double& tMin) const
{
	double a = v0.xPoint - v1.xPoint;
    double b = v0.xPoint - v2.xPoint;
	double c = ra.dir.xPoint;
    double d = v0.xPoint - ra.orig.xPoint;
	double e = v0.yPoint - v1.yPoint;
    double f = v0.yPoint - v2.yPoint;
	double g = ra.dir.yPoint;
    double h = v0.yPoint - ra.orig.yPoint;
	double i = v0.zPoint - v1.zPoint;
    double j = v0.zPoint - v2.zPoint;
	double k = ra.dir.zPoint;
    double l = v0.zPoint - ra.orig.zPoint;

	double m = f * k - g * j;
    double n = h * k - g * l;
	double p = f * l - h * j;
    double q = g * i - e * k;
	double s = e * j - f * i;

	double invDenom = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * invDenom;

	// first check
	if (beta < 0.0)
	{
		return false;
	}

	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * invDenom;

	// second check
	if (gamma < 0.0)
	{
		return false;
	}

	// third check
	if (beta + gamma > 1.0)
	{
		return false;
	}

	double e3 = a * p - b * r + d * s;
	double t = e3 * invDenom;

	// final check
	if (t < kEpsilon)
	{
		return false;
	}

	//hit
	tMin = t;

	return true;
}

bool Triangle::getBoundingBox(AABB& outputBox) const
{
	double delta = 0.00001;
	Point3 ansMin, ansMax;
	//p0
	ansMin.xPoint = min( {v0.xPoint,v1.xPoint,v2.xPoint}  );
	ansMin.yPoint = min( {v0.yPoint,v1.yPoint,v2.yPoint} );
	ansMin.zPoint = min( {v0.zPoint,v1.zPoint,v2.zPoint} );
	//p1
	ansMax.xPoint = max( {v0.xPoint,v1.xPoint,v2.xPoint} );
	ansMax.yPoint = max( {v0.yPoint,v1.yPoint,v2.yPoint} );
	ansMax.zPoint = max( {v0.zPoint,v1.zPoint,v2.zPoint} );

	//minus or plus delta ,It means make BBox
	ansMin = ansMin - Vec3(0.00001);
	ansMax = ansMax + delta;
    outputBox = AABB(ansMin, ansMax);
	return true;
} 

Vec3 Triangle::getFaceNormal() const {
	Vec3 e1 = v1 - v0;
	Vec3 e2 = v2 - v0;
	return e1^e2;
}