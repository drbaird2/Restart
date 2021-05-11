#ifndef POINT3_H
#define POINT3_H

#include "Matrix.h"
#include "Vec3.h"

class Point3 {
	public:
	
		double xPoint, yPoint, zPoint;
	
		Point3();													// default constructor
		Point3(const double a);									// constructor
		Point3(const double a, const double b, const double c);	// constructor
		Point3(const Point3& p);									// copy constructor
		~Point3();													// destructor
		
		Point3& 													// assignment operator
		operator= (const Point3& p);
		
		Point3 													// unary minus
		operator- (void) const;
	
		Vec3 													// vector joining two points
		operator- (const Point3& p) const;
		
		Point3 													// addition of a vector				
		operator+ (const Vec3& v) const;
		
		Point3 													// subtraction of a vector
		operator- (const Vec3& v) const;
				
		Point3 													// multiplication by a double on the right
		operator* (const double a) const;

        Point3 operator- (const double a) const;
		
		double														// square of distance bertween two points
		d_squared(const Point3& p) const;
		
		double														// distance bewteen two points
		distance(const Point3& p) const;
};



// inlined member functions

// -------------------------------------------------------------- operator-
// unary minus

inline Point3 Point3::operator- (void) const {
	return (Point3(-xPoint, -yPoint, -zPoint));
}


// -------------------------------------------------------------- operator-
// the vector that joins two points

inline Vec3 Point3::operator- (const Point3& p) const {
	return (Vec3(xPoint - p.xPoint,yPoint - p.yPoint,zPoint - p.zPoint));
}


// -------------------------------------------------------------- operator+
// addition of a vector to a point that returns a new point

inline Point3 Point3::operator+ (const Vec3& v) const {
	return (Point3(xPoint + v.xPoint, yPoint + v.yPoint, zPoint + v.zPoint));
}


// -------------------------------------------------------------- operator-
// subtraction of a vector from a point that returns a new point

inline Point3 Point3::operator- (const Vec3& v) const {
	return (Point3(xPoint - v.xPoint, yPoint - v.yPoint, zPoint - v.zPoint));
}


// -------------------------------------------------------------- operator*
// mutliplication by a double on the right

inline Point3 Point3::operator* (const double a) const {
	return (Point3(xPoint * a,yPoint * a,zPoint * a));
}


// -------------------------------------------------------------- d_squared
// the square of the distance between the two points as a member function

inline double Point3::d_squared(const Point3& p) const {
	return (	(xPoint - p.xPoint) * (xPoint - p.xPoint) 
			+ 	(yPoint - p.yPoint) * (yPoint - p.yPoint)
			+	(zPoint - p.zPoint) * (zPoint - p.zPoint) );
}




// inlined non-member function

// -------------------------------------------------------------- operator*
// multiplication by a double on the left

Point3												// prototype
operator* (double a, const Point3& p);

inline Point3 operator* (double a, const Point3& p) {
	return (Point3(a * p.xPoint, a * p.yPoint, a * p.zPoint));
}



// non-inlined non-member function

// -------------------------------------------------------------- operator*
// multiplication by a matrix on the left

Point3 											// prototype					
operator* (const Matrix& mat, const Point3& p);

#endif