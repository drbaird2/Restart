#include "AABB.h"
#include "../Utilities/Constants.h"

AABB::AABB()
	: p0(Point3(0.0,0.0,0.0))
	, p1(Point3(0.0,0.0,0.0))
{
	centroid = (p0 + p1) / 2;
}
AABB::AABB(Point3 p0, Point3 p1)
	: p0(p0)
	, p1(p1)
{
	centroid = (p0 + p1) / 2;	
}

AABB::AABB(const AABB& aab)
	: p0(aab.p0)
	, p1(aab.p1)
{
	centroid = (p0 + p1) / 2;
}

shared_ptr<AABB> AABB::clone() const
{
	return make_shared<AABB>(*this);
}

AABB& AABB::operator=(const AABB& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	p0 = rhs.p0;
	p1 = rhs.p1;

	return *this;
}

AABB::~AABB()
{
}



bool AABB::intersect(const Ray& ra, double& t, Record& recentHits) const
{
	Point3 origin = Point3(ra.orig);
	Point3 dir = Point3(ra.dir.xPoint, ra.dir.yPoint, ra.dir.zPoint);
	Point3 tMin;
	Point3 tMax;

	double a = 1.0 / dir.xPoint;
	if (a >= 0)
	{
		tMin.xPoint = (p0.xPoint - origin.xPoint) * a;
		tMax.xPoint = (p1.xPoint - origin.xPoint) * a;
	}
	else
	{
		tMin.xPoint = (p1.xPoint - origin.xPoint) * a;
		tMax.xPoint = (p0.xPoint - origin.xPoint) * a;
	}

	double b = 1.0 / dir.yPoint;
	if (b >= 0)
	{
		tMin.yPoint = (p0.yPoint - origin.yPoint) * b;
		tMax.yPoint = (p1.yPoint - origin.yPoint) * b;
	}
	else
	{
		tMin.yPoint = (p1.yPoint - origin.yPoint) * b;
		tMax.yPoint = (p0.yPoint - origin.yPoint) * b;
	}

	double c = 1.0 / dir.zPoint;
	if (c >= 0)
	{
		tMin.zPoint = (p0.zPoint - origin.zPoint) * c;
		tMax.zPoint = (p1.zPoint - origin.zPoint) * c;
	}
	else
	{
		tMin.zPoint = (p1.zPoint - origin.zPoint) * c;
		tMax.zPoint = (p0.zPoint - origin.zPoint) * c;
	}

	double t0, t1;
	//finding largest t
	if (tMin.xPoint > tMin.yPoint)
	{
		t0 = tMin.xPoint;
	}
	else
	{
		t0 = tMin.yPoint;
	}

	if (tMin.zPoint > t0)
	{
		t0 = tMin.zPoint;
	}

	//finding smallest
	if (tMax.xPoint < tMax.yPoint)
	{
		t1 = tMax.xPoint;
	}
	else
	{
		t1 = tMax.yPoint;
	}

	if (tMax.zPoint < t1)
	{
		t1 = tMax.zPoint;
	}

	return (t0 < t1 && t1 > kEpsilon);
}
/* bool AABB::inside(const Point3& p) const
{
	return (p.xPoint > p0.xPoint&& p.xPoint < p1.xPoint) &&
		(p.yPoint > p0.yPoint&& p.yPoint < p1.yPoint) &&
		(p.zPoint > p1.zPoint&& p.zPoint < p1.zPoint);
} */

double AABB::area() const{
	auto a = p1.xPoint - p0.xPoint;
	auto b = p1.yPoint - p0.yPoint;
	auto c = p1.zPoint - p0.zPoint;
	return 2*(a*b + b*c + c*a);
}

int AABB::longest_axis() const{
	auto a = p1.xPoint - p0.xPoint;
	auto b = p1.yPoint - p0.yPoint;
	auto c = p1.zPoint - p0.zPoint;
	if(a>b && a>c){
		return 0;
	} else if(b>c){
		return 1;
	}else{
		return 2;
	}
}

AABB AABB::surroundingBox(AABB box0, AABB box1){
	Point3 small(fmin(box0.p0.xPoint, box1.p0.xPoint),
                 fmin(box0.p0.yPoint, box1.p0.yPoint),
                 fmin(box0.p0.zPoint, box1.p0.zPoint));
	Point3 big(fmax(box0.p1.xPoint, box1.p1.xPoint),
               fmax(box0.p1.yPoint, box1.p1.yPoint),
               fmax(box0.p1.zPoint, box1.p1.zPoint));
//	std::cout << "surrounding box: " << &box0 << " and " << &box1 << endl;
	
	return AABB(small,big);
}

bool AABB::shadowIntersect(const Ray& ra, double& t) const
{
	Point3 origin = Point3(ra.orig);
	Point3 dir = Point3(ra.dir.xPoint, ra.dir.yPoint, ra.dir.zPoint);
	Point3 tMin;
	Point3 tMax;

	double a = 1.0 / dir.xPoint;
	if (a >= 0)
	{
		tMin.xPoint = (p0.xPoint - origin.xPoint) * a;
		tMax.xPoint = (p1.xPoint - origin.xPoint) * a;
	}
	else
	{
		tMin.xPoint = (p1.xPoint - origin.xPoint) * a;
		tMax.xPoint = (p0.xPoint - origin.xPoint) * a;
	}

	double b = 1.0 / dir.yPoint;
	if (b >= 0)
	{
		tMin.yPoint = (p0.yPoint - origin.yPoint) * b;
		tMax.yPoint = (p1.yPoint - origin.yPoint) * b;
	}
	else
	{
		tMin.yPoint = (p1.yPoint - origin.yPoint) * b;
		tMax.yPoint = (p0.yPoint - origin.yPoint) * b;
	}

	double c = 1.0 / dir.zPoint;
	if (c >= 0)
	{
		tMin.zPoint = (p0.zPoint - origin.zPoint) * c;
		tMax.zPoint = (p1.zPoint - origin.zPoint) * c;
	}
	else
	{
		tMin.zPoint = (p1.zPoint - origin.zPoint) * c;
		tMax.zPoint = (p0.zPoint - origin.zPoint) * c;
	}

	double t0, t1;
	//finding largest t
	if (tMin.xPoint > tMin.yPoint)
	{
		t0 = tMin.xPoint;
	}
	else
	{
		t0 = tMin.yPoint;
	}

	if (tMin.zPoint > t0)
	{
		t0 = tMin.zPoint;
	}

	//finding smallest
	if (tMax.xPoint < tMax.yPoint)
	{
		t1 = tMax.xPoint;
	}
	else
	{
		t1 = tMax.yPoint;
	}

	if (tMax.zPoint < t1)
	{
		t1 = tMax.zPoint;
	}

	return (t0 < t1 && t1 > kEpsilon);
}
