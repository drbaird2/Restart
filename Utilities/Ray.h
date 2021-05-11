#ifndef RAY_H
#define RAY_H

#include "Vec3.h"
#include "Point3.h"

class Ray{
    public:
        Point3 orig;
        Vec3 dir;
    public:
        Ray();
        Ray(const Point3& origin, const Vec3& dir);
        Ray(const Ray& ra);

        ~Ray();

        Ray& operator= (const Ray& rhs);

};



#endif