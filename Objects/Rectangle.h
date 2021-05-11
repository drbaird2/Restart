#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Object.h"
#include "../Utilities/Point3.h"
#include "../Utilities/Vec3.h"
#include "../Utilities/Normal.h"
#include "../Samplers/Sampler.h"
#include "../Utilities/Ray.h"
#include "../Utilities/Record.h"

class Rectangle : public Object
{
public:
	Rectangle();
	Rectangle(Point3 p0, Vec3 a, Vec3 b, Normal n);
	Rectangle(Point3 p0, Vec3 a, Vec3 b);
	Rectangle(const Rectangle& rect);
	Rectangle& operator=(const Rectangle& rhs);
	std::shared_ptr<Rectangle> clone() const;
	~Rectangle();

	virtual bool intersect(const Ray& ray, double& tMin, Record& recentHits);
	bool shadowIntersect(const Ray& ray, double& tMin) const override;

	void SetP0(const Point3 p0);
	Point3 GetP0() const;
	void SetAB(Vec3 a, Vec3 b);
	void SetSampler(shared_ptr<Sampler> sampler);
	Point3 sample() override;
	float pdf(const Record& recentHits) override;
	Normal getNormal(const Point3& p) override;
private:
	Point3 P0;
	Vec3 A;
	Vec3 B;
	Normal norm;
	std::shared_ptr<Sampler> samplePtr;
	float area;
	float invArea;
	float aLenSquared;
	float bLenSquared;
};

#endif