#include "Box.h"
#include "../Utilities/Constants.h"

Box::Box(const Point3& p0, const Point3& p1)
	: Object()
	, P0(p0)
	, P1(p1)
{
}

Box::Box(const Box& box)
	: Object(box)
	, P0(box.P0)
	, P1(box.P1)
{
}

Box::~Box()
{
}

Box& Box::operator=(Box& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Object::operator=(rhs);
	P0 = rhs.P0;
	P1 = rhs.P1;

	return *this;
}

std::shared_ptr<Box> Box::clone() const
{
	return std::make_shared<Box>(*this);
}

bool Box::intersect(const Ray& ray, double& t, Record& recentHits)
{
	Point3 origin(ray.orig);
	Point3 dir(ray.dir.xPoint,ray.dir.yPoint,ray.dir.zPoint);
	Point3 tMin;
	Point3 tMax;

	double a = 1.0 / dir.xPoint;
	if (a >= 0)
	{
		tMin.xPoint = (P0.xPoint - origin.xPoint) * a;
		tMax.xPoint = (P1.xPoint - origin.xPoint) * a;
	}
	else
	{
		tMin.xPoint = (P1.xPoint - origin.xPoint) * a;
		tMax.xPoint = (P0.xPoint - origin.xPoint) * a;
	}

	double b = 1.0 / dir.yPoint;
	if (b >= 0)
	{
		tMin.yPoint = (P0.yPoint - origin.yPoint) * b;
		tMax.yPoint = (P1.yPoint - origin.yPoint) * b;
	}
	else
	{
		tMin.yPoint = (P1.yPoint - origin.yPoint) * b;
		tMax.yPoint = (P0.yPoint - origin.yPoint) * b;
	}

	double c = 1.0 / dir.zPoint;
	if (c >= 0)
	{
		tMin.zPoint = (P0.zPoint - origin.zPoint) * c;
		tMax.zPoint = (P1.zPoint - origin.zPoint) * c;
	}
	else
	{
		tMin.zPoint = (P1.zPoint - origin.zPoint) * c;
		tMax.zPoint = (P0.zPoint - origin.zPoint) * c;
	}

	double t0, t1;
	int faceIn, faceOut;
	
	//find largest
	if (tMin.xPoint > tMin.yPoint)
	{
		t0 = tMin.xPoint;
		faceIn = (a >= 0.0) ? 0 : 3;
	}
	else
	{
		t0 = tMin.yPoint;
		faceIn = (b >= 0.0) ? 1 : 4;
	}
	if (tMin.zPoint > t0)
	{
		t0 = tMin.zPoint;
		faceIn = (c >= 0.0) ? 2 : 5;
	}

	//find smallest
	if (tMax.xPoint < tMax.yPoint)
	{
		t1 = tMax.xPoint;
		faceOut = (a >= 0.0) ? 3 : 0;
	}
	else
	{
		t1 = tMax.yPoint;
		faceOut = (b >= 0.0) ? 4 : 1;
	}
	if (tMax.zPoint < t1)
	{
		t1 = tMax.zPoint;
		faceOut = (c >= 0.0) ? 5 : 2;
	}

	if ((t0 < t1) && (t1 > kEpsilon))
	{
		if (t0 > kEpsilon)
		{
			t = t0;
			recentHits.sceneNormal = GetNormal(faceIn);
		}
		else
		{
			t = t1;
			recentHits.sceneNormal  = GetNormal(faceOut);
		}

		recentHits.localHit = ray.orig + t * ray.dir;
        recentHits.material_ptr = getMaterial();
		return true;
	}
	else
	{
		return false;
	}
}

bool Box::shadowIntersect(const Ray& ray, double& t) const
{
	Point3 origin(ray.orig);
	Point3 dir(ray.dir.xPoint, ray.dir.yPoint, ray.dir.zPoint);
	Point3 tMin;
	Point3 tMax;

	double a = 1.0 / dir.xPoint;
	if (a >= 0)
	{
		tMin.xPoint = (P0.xPoint - origin.xPoint) * a;
		tMax.xPoint = (P1.xPoint - origin.xPoint) * a;
	}
	else
	{
		tMin.xPoint = (P1.xPoint - origin.xPoint) * a;
		tMax.xPoint = (P0.xPoint - origin.xPoint) * a;
	}

	double b = 1.0 / dir.yPoint;
	if (b >= 0)
	{
		tMin.yPoint = (P0.yPoint - origin.yPoint) * b;
		tMax.yPoint = (P1.yPoint - origin.yPoint) * b;
	}
	else
	{
		tMin.yPoint = (P1.yPoint - origin.yPoint) * b;
		tMax.yPoint = (P0.yPoint - origin.yPoint) * b;
	}

	double c = 1.0 / dir.zPoint;
	if (c >= 0)
	{
		tMin.zPoint = (P0.zPoint - origin.zPoint) * c;
		tMax.zPoint = (P1.zPoint - origin.zPoint) * c;
	}
	else
	{
		tMin.zPoint = (P1.zPoint - origin.zPoint) * c;
		tMax.zPoint = (P0.zPoint - origin.zPoint) * c;
	}

	double t0, t1;
	int faceIn, faceOut;

	//find largest
	if (tMin.xPoint > tMin.yPoint)
	{
		t0 = tMin.xPoint;
		faceIn = (a >= 0.0) ? 0 : 3;
	}
	else
	{
		t0 = tMin.yPoint;
		faceIn = (b >= 0.0) ? 1 : 4;
	}
	if (tMin.zPoint > t0)
	{
		t0 = tMin.zPoint;
		faceIn = (c >= 0.0) ? 2 : 5;
	}

	//find smallest
	if (tMax.xPoint < tMax.yPoint)
	{
		t1 = tMax.xPoint;
		faceOut = (a >= 0.0) ? 3 : 0;
	}
	else
	{
		t1 = tMax.yPoint;
		faceOut = (b >= 0.0) ? 4 : 1;
	}
	if (tMax.zPoint < t1)
	{
		t1 = tMax.zPoint;
		faceOut = (c >= 0.0) ? 5 : 2;
	}

	if (t0 < t1 && t1 > kEpsilon)
	{
		if (t0 > kEpsilon)
		{
			t = t0;
		}
		else
		{
			t = t1;
		}
		return true;
	}
	else
	{
		return false;
	}
}

Normal Box::GetNormal(const int faceHit) const
{
	switch (faceHit)
	{
	case 0: return Normal(-1, 0, 0); //-x face
	case 1: return Normal(0, -1, 0); //-y face
	case 2: return Normal(0, 0, -1); //-z face
	case 3: return Normal(1, 0, 0);  //+x face
	case 4: return Normal(0, 1, 0);  //+y face
	case 5: return Normal(0, 0, 1);  //+z face
	}
    return Normal(0,0,0);
}

bool Box::getBoundingBox(AABB& outputBox) const
{
	outputBox =  AABB(P0-kEpsilon,P1+kEpsilon);
    return true;
}

void Box::SetP0(const Point3 p0)
{
	P0 = p0;
}

Point3 Box::GetP0() const
{
	return P0;
}

void Box::SetP1(const Point3 p1)
{
	P1 = p1;
}

Point3 Box::GetP1() const
{
	return P1;
}