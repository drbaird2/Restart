#ifndef BOX_H
#define BOX_H

#include "Object.h"
#include "../Utilities/Point3.h"
#include "../Utilities/Record.h"
#include "../Utilities/Ray.h"
#include "../Utilities/Normal.h"

class Box : public Object
{
public:
	Box(const Point3& p0, const Point3& p1);
	Box(const Box& box);
	~Box();
	Box& operator=(Box& rhs);

	std::shared_ptr<Box> clone() const;
	virtual bool intersect(const Ray& ray, double& t, Record& recentHits);
	bool shadowIntersect(const Ray& ray, double& t) const override;
	Normal GetNormal(const int faceHit) const;
	bool getBoundingBox(AABB& outputBox) const override;

	void SetP0(const Point3 p0);
	Point3 GetP0() const;
	void SetP1(const Point3 p1);
	Point3 GetP1() const;

public:
	Point3 P0;
	Point3 P1;
};

#endif