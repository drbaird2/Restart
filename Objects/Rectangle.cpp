#include "Rectangle.h"
#include "../Utilities/Constants.h"

Rectangle::Rectangle()
	: Object()
	, P0(-1,0,-1)
	, A(0,0,2)
	, B(2,0,0)
	, aLenSquared(4.0)
	, bLenSquared(4.0)
	, norm(0,1,0)
	, area(4.0)
	, invArea(0.25)
	, samplePtr(nullptr)
{
}

Rectangle::Rectangle(Point3 p0, Vec3 a, Vec3 b, Normal n)
	: Object()
	, P0(p0)
	, A(a)
	, B(b)
	, norm(n)
	, samplePtr(nullptr)
	, area(a.length() * b.length())
	, invArea(1.0/area)
	, aLenSquared(a.length_squared())
	, bLenSquared(b.length_squared())
{
	norm.normalize();
}

Rectangle::Rectangle(Point3 p0, Vec3 a, Vec3 b)
	: Object()
	, P0(p0)
	, A(a)
	, B(b)
	, aLenSquared(a.length_squared())
	, bLenSquared(b.length_squared())
	, area(a.length() * b.length())
	, invArea(1.0/area)
	, samplePtr(nullptr)
{
	norm = a ^ b;
	norm.normalize();
}

Rectangle::Rectangle(const Rectangle& rect)
	: Object(rect)
	, P0(rect.P0)
	, A(rect.A)
	, B(rect.B)
	, norm(rect.norm)
	, area(rect.area)
	, invArea(rect.invArea)
	, aLenSquared(rect.aLenSquared)
	, bLenSquared(rect.bLenSquared)
{
	if (rect.samplePtr)
	{
		samplePtr = rect.samplePtr->clone();
	}
	else
	{
		samplePtr = nullptr;
	}
}

Rectangle& Rectangle::operator=(const Rectangle& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Object::operator=(rhs);
	P0 = rhs.P0;
	A = rhs.A;
	B = rhs.B;
	norm = rhs.norm;
	area = rhs.area;
	invArea = rhs.invArea;
	aLenSquared = rhs.aLenSquared;
	bLenSquared = rhs.bLenSquared;
	if (rhs.samplePtr)
	{
		samplePtr = rhs.samplePtr->clone();
	}
	else
	{
		samplePtr = nullptr;
	}

	return *this;
}

shared_ptr<Rectangle> Rectangle::clone() const
{
	return make_shared<Rectangle>(*this);
}

Rectangle::~Rectangle()
{
}

bool Rectangle::intersect(const Ray& ray, double& tMin, Record& recentHits)
{
	double t = (P0 - ray.orig) * norm / (ray.dir * norm);

	if (t <= kEpsilon)
	{
		return false;
	}

	Point3 p = ray.orig + t * ray.dir;
	Vec3 d = p - P0;
	
	double ddota = d * A;

	if ((ddota < 0.0) || (ddota > aLenSquared))
	{
		return false;
	}

	double ddotb = d * B;
	if((ddotb <0.0) || (ddotb > bLenSquared))
	{
		return false;
	}

	tMin = t;
	recentHits.sceneNormal = norm;
	recentHits.localHit = p;
    recentHits.material_ptr = getMaterial();
	return true;
}

bool Rectangle::shadowIntersect(const Ray& ray, double& tMin) const
{
	double t = (P0 - ray.orig) * norm / (ray.dir * norm);

	if (t <= kEpsilon)
	{
		return false;
	}

	Point3 p = ray.orig + t * ray.dir;
	Vec3 d = p - P0;

	double ddota = d * A;

	if ((ddota < 0.0) || (ddota > aLenSquared))
	{
		return false;
	}

	double ddotb = d * B;
	if ((ddotb <0.0) || (ddotb > bLenSquared))
	{
		return false;
	}

	tMin = t;

	return true;
}

void Rectangle::SetP0(const Point3 p0)
{
	P0 = p0;
}

Point3 Rectangle::GetP0() const
{
	return P0;
}

void Rectangle::SetAB(Vec3 a, Vec3 b)
{
	A = a;
	B = b;
	norm = a ^ b;
	norm.normalize();
	area = a.length() * b.length();
	invArea = 1.0 / area;
	aLenSquared = a.length_squared();
	bLenSquared = b.length_squared();
}

void Rectangle::SetSampler(shared_ptr<Sampler> sampler)
{
	samplePtr = sampler;
}

Point3 Rectangle::sample()
{
	Point2 samplePoint = samplePtr->sampleUnitSquare();
	return (P0 + samplePoint.xPoint * A + samplePoint.yPoint * B);
}

float Rectangle::pdf(const Record& recentHits)
{
	return invArea;
}

Normal Rectangle::getNormal(const Point3& p)
{
	return norm;
}