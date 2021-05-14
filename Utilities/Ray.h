#ifndef RAY_H
#define RAY_H

#include "Vec3.h"
#include "Point3.h"

/*******************************************************************
 * Class - Ray - Represents a ray shot from the eye to a point on the 
 *                 Viewplane. consists of an origin and a direction
 * 
 * Variables
 * Point3 orig - the origin point of the ray
 * Vec3 dir - the direction vector of the ray
 *******************************************************************/


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