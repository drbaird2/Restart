#include "Ray.h"

Ray::Ray():
    orig(0.0, 0.0, 0.0),
    dir(0.0, 0.0, 1.0)
{}

Ray::Ray(const Point3& origin, const Vec3& direction):
    orig(origin), dir(direction)
{}

Ray::Ray(const Ray& rhs):
    orig(rhs.orig),
    dir(rhs.dir)
{}

Ray::~Ray()
{}

Point3 Ray::at(double t) {
    return orig + dir * t;
}