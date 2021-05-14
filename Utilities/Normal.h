#ifndef NORMAL_H
#define NORMAL_H

#include "Matrix.h"
#include "Vec3.h"
#include "Point3.h"

/*******************************************************************
 * class - Normal
 * 
 * A Utility class that represents a Normal vector
 * 
 * Variables
 * double xPoint - represents the x value of the Normal
 * double yPoint - represents the y value of the Normal
 * double zPoint - represents the z value of the Normal
 * 
 * See Vec3 for Documentation
 * 
 * normalize() is the same function as unit_vector()
 * 
 *******************************************************************/


class Normal {	
	public:
	
		double	xPoint, yPoint, zPoint;
				
	public:
	
		Normal(void);										
		Normal(double a);									
		Normal(double x, double y, double z);		
		Normal(const Normal& n); 				
		Normal(const Vec3& v);
		
		~Normal(void);

		Normal& operator= (const Normal& rhs); 	
		
		Normal& operator= (const Vec3& rhs);
		
		Normal& operator= (const Point3& rhs);
		
		Normal operator- (void) const;	
		
		Normal operator+ (const Normal& n) const;
		
		Normal& operator+= (const Normal& n);
		
		double operator* (const Vec3& v) const;				
		
		Normal operator* (const double a) const;
				
		void normalize(void); 									 		
};


inline Normal Normal::operator- (void) const {
	return (Normal(-xPoint, -yPoint, -zPoint));
}

inline Normal Normal::operator+ (const Normal& n) const {
	return (Normal(xPoint + n.xPoint, yPoint + n.yPoint, zPoint + n.zPoint));
}

inline Normal& Normal::operator+= (const Normal& n) {
	xPoint += n.xPoint; 
    yPoint += n.yPoint; 
    zPoint += n.zPoint;
    return (*this);
}


inline double Normal::operator* (const Vec3& v) const {
	return (xPoint * v.xPoint + yPoint * v.yPoint + zPoint * v.zPoint);
}


inline Normal Normal::operator* (const double a) const {
	return (Normal(xPoint * a, yPoint * a, zPoint * a));
}

Normal operator* (const double a, const Normal& n);

inline Normal operator*(const double f, const Normal& n) {
	return (Normal(f * n.xPoint, f * n.yPoint,f * n.zPoint));
}


Vec3 operator+ (const Vec3& v, const Normal& n);

inline Vec3 operator+ (const Vec3& v, const Normal& n) {	
	return (Vec3(v.xPoint + n.xPoint, v.yPoint + n.yPoint, v.zPoint + n.zPoint));
}	


Vec3 operator- (const Vec3&, const Normal& n);

inline Vec3 operator- (const Vec3& v, const Normal& n) {
	return (Vec3(v.xPoint - n.xPoint, v.yPoint - n.yPoint, v.zPoint - n.zPoint));
}

double operator* (const Vec3& v, const Normal& n);

inline double operator* (const Vec3& v, const Normal& n) {
	return (v.xPoint * n.xPoint + v.yPoint * n.yPoint + v.zPoint * n.zPoint);     
}

Normal operator* (const Matrix& mat, const Normal& n);

#endif