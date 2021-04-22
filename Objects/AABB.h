#ifndef AABB_H
#define AABB_H


#include "..\Utilities\Vec3.h"
#include "..\Utilities\Ray.h"
#include <memory>

using namespace std;

class AABB {
public:
    AABB();
	AABB(Point3 p0, Point3 p1);
	AABB(const AABB& aabbox);
	shared_ptr<AABB> clone() const;
	AABB& operator=(const AABB& rhs);
	~AABB();

	bool intersect(const Ray& ray) const;
	bool inside(const Point3& p) const;
	Point3 p0;
	Point3 p1;
};

#endif