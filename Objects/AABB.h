#ifndef AABB_H
#define AABB_H


#include "..\Utilities\Vec3.h"
#include "..\Utilities\Ray.h"
#include <memory>

class Record;

using namespace std;

class AABB {
public:
    AABB();
	AABB(Point3 p0, Point3 p1);
	AABB(const AABB& aabbox);
	shared_ptr<AABB> clone() const;
	AABB& operator=(const AABB& rhs);
	~AABB();

	bool intersect(const Ray& ray, double& t, Record& recentHits) const;
	bool shadowIntersect(const Ray& ra, double& tmin) const;

	int longest_axis() const;
	double area() const;

//	bool inside(const Point3& p) const;
	AABB surroundingBox(AABB box0, AABB box1);

	Point3 cen() const;
	Point3 p0;
	Point3 p1;
	Point3 centroid;
};

inline Point3 AABB::cen() const{
	return centroid;
}
#endif