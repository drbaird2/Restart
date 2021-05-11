#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"
#include "../Utilities/Record.h"
#include "../Utilities/Ray.h"
#include "../Utilities/Point3.h"



class Sphere : public Object {
    public:
        double radius;
        Point3 center;
        
    public:
        Sphere();
        Sphere( Point3 cen, double rad);
        Sphere( const Sphere& sphere);
        virtual ~Sphere();

        virtual shared_ptr<Sphere> clone() const;

        void setRadius(const double rad);
        void setCenter(const Point3& cen);
        void setCenter(const double x, const double y, const double z);

        Sphere& operator=(const Sphere& sphere);

        //The intersect function using the quadratic equation.
        virtual bool intersect(const Ray& ra, double& t, Record& recentHits) override;  
        virtual bool shadowIntersect(const Ray& ra, double& tmin) const override;
        bool getBoundingBox(AABB& outputBox) const override;
    
        
};

       
inline void Sphere::setRadius(double rad){
    radius = rad;
}
inline void Sphere::setCenter(const Point3& cen){
    center = cen;
}
inline void Sphere::setCenter(const double x, const double y, const double z){
    center = Point3(x,y,z);
}

inline Sphere& Sphere::operator=(const Sphere& rhs)
{
	if (this == &rhs)
	{
		return (*this);
	}
	center = rhs.center;
	radius = rhs.radius;

	return (*this);
}

#endif 

