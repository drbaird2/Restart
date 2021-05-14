#ifndef POINT3_H
#define POINT3_H

#include "Matrix.h"
#include "Vec3.h"

/*******************************************************************
 * Class Point3 - Similar to a vector, but represents a single 3 Dimensional Point
 * 
 * Variables
 * double xPoint - represents the x value of the Point
 * double yPoint - represents the y value of the Point
 * double zPoint - represents the z value of the Point
 * 
 * Has two unique functions from Vectors
 * d_Squared and Distance
 * 
 *******************************************************************/
class Point3 {
	public:
	
		double xPoint, yPoint, zPoint;
	
		Point3();												
		Point3(const double a);									
		Point3(const double a, const double b, const double c);	
		Point3(const Point3& p);								
		~Point3();												
		
		Point3& operator= (const Point3& p);
		
		Point3 operator- (void) const;
	
		Vec3 operator- (const Point3& p) const;
		
		Point3 operator+ (const Vec3& v) const;
		
		Point3 operator- (const Vec3& v) const;
				
		Point3 operator* (const double a) const;

        Point3 operator- (const double a) const;
		
		double d_squared(const Point3& p) const;
		
		double distance(const Point3& p) const;
};


inline Point3 Point3::operator- (void) const {
	return (Point3(-xPoint, -yPoint, -zPoint));
}

inline Vec3 Point3::operator- (const Point3& p) const {
	return (Vec3(xPoint - p.xPoint,yPoint - p.yPoint,zPoint - p.zPoint));
}

inline Point3 Point3::operator+ (const Vec3& v) const {
	return (Point3(xPoint + v.xPoint, yPoint + v.yPoint, zPoint + v.zPoint));
}

inline Point3 Point3::operator- (const Vec3& v) const {
	return (Point3(xPoint - v.xPoint, yPoint - v.yPoint, zPoint - v.zPoint));
}

inline Point3 Point3::operator* (const double a) const {
	return (Point3(xPoint * a,yPoint * a,zPoint * a));
}

/*******************************************************************
 * d_squared(Point3) - Takes the given point and returns the square 
 * 						of the distance between the current point and 
 * 						the given one.
 * 
 *******************************************************************/
inline double Point3::d_squared(const Point3& p) const {
	return (	(xPoint - p.xPoint) * (xPoint - p.xPoint) 
			+ 	(yPoint - p.yPoint) * (yPoint - p.yPoint)
			+	(zPoint - p.zPoint) * (zPoint - p.zPoint) );
}

Point3 operator* (double a, const Point3& p);

inline Point3 operator* (double a, const Point3& p) {
	return (Point3(a * p.xPoint, a * p.yPoint, a * p.zPoint));
}

Point3 operator* (const Matrix& mat, const Point3& p);

#endif