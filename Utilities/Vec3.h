#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include "Matrix.h"

class Normal;
class Point3;


using std::sqrt;
using std::fabs;


/*******************************************************************
 * class - Vec3
 * 
 * A Utility class that represents a Vector
 * 
 * Variables
 * double xPoint - represents the x value of the vector
 * double yPoint - represents the y value of the vector
 * double zPoint - represents the z value of the vector
 * 
 *******************************************************************/

class Vec3{
    public:
        double xPoint, yPoint, zPoint;

    public:
        Vec3();
        Vec3(double a);
        Vec3(double x, double y, double z);
        Vec3(const Vec3& v);
        Vec3(const Normal& n);
        Vec3(const Point3& p);

        ~Vec3 (void);


        Vec3 operator-() const;

        Vec3& operator= (const Vec3& rhs);					
        Vec3& operator= (const Normal& rhs);				
        Vec3& operator= (const Point3& rhs); 				
		
        double length(void);
        double length_squared(void);



        Vec3& operator+=(const Vec3 &v);
        Vec3& operator*=(const double t);
        Vec3& operator/=(const double t);

        std::ostream& operator<<(std::ostream &out);
        
        Vec3 operator* (const double a) const;												
		
        Vec3 operator/ (const double a) const;									 
        Vec3 operator+ (const Vec3& v) const;
										
        Vec3 operator- (const Vec3& v) const;		
		
		
        double operator* (const Vec3 &v) const;
        Vec3 operator^ (const Vec3 &v) const;
        void unit_vector();
};

/*******************************************************************
 * Inlined Member functions
 * 
 * Unary Minus - allows the reversal of the current vector without altering it.
 * 
 * len_squared - Returns the square of the length of the current vector
 * 
 * Opperator functions for * with doubles as well as the dot product
 * Opperator functions for -, /, +, and compound versions +=,-=,*=, and /=
 * Opperator function for ^ to represent cross products.
 * Opperator function for << to print out values.
 * 
 *******************************************************************/

inline Vec3 Vec3::operator- (void) const {
	return (Vec3 (-xPoint, -yPoint, -zPoint));    
}


// ---------------------------------------------------------------------  len_squared
// the square of the length

inline double Vec3::length_squared(void) {	
	return (xPoint * xPoint + yPoint * yPoint + zPoint * zPoint);
}


// ----------------------------------------------------------------------- operator*
// multiplication by a double on the right

inline Vec3  Vec3 ::operator* (const double a) const {	
	return (Vec3 (xPoint * a, yPoint * a, zPoint * a));	
}

// ----------------------------------------------------------------------- operator/
// division by a double

inline Vec3 Vec3 ::operator/ (const double a) const {	
	return (Vec3 (xPoint / a, yPoint / a, zPoint / a));	
}


// ----------------------------------------------------------------------- operator+
// addition

inline Vec3  Vec3 ::operator+ (const Vec3 & v) const {
	return (Vec3 (xPoint + v.xPoint, yPoint + v.yPoint, zPoint + v.zPoint));
}


// ----------------------------------------------------------------------- operator-
// subtraction

inline Vec3 Vec3 ::operator- (const Vec3 & v) const {
	return (Vec3 (xPoint - v.xPoint, yPoint - v.yPoint, zPoint - v.zPoint));
}


// ----------------------------------------------------------------------- operator*
// dot product

inline double Vec3 ::operator* (const Vec3 & v) const {
	return (xPoint * v.xPoint + yPoint * v.yPoint + zPoint * v.zPoint);
} 


// ----------------------------------------------------------------------- operator^
// cross product

inline Vec3 Vec3 ::operator^ (const Vec3 & v) const {
	return (Vec3 (yPoint * v.zPoint - zPoint * v.yPoint, zPoint * v.xPoint - xPoint * v.zPoint, xPoint * v.yPoint - yPoint * v.xPoint));
}


// ---------------------------------------------------------------------  operator+=
// compound addition

inline Vec3& Vec3 ::operator+= (const Vec3 & v) {
	xPoint += v.xPoint; yPoint += v.yPoint; zPoint += v.zPoint;
	return (*this);
}

inline std::ostream& Vec3::operator<<(std::ostream &out){
    return out << xPoint << ' ' << yPoint << ' ' << zPoint;
}



// inlined non-member function

// ----------------------------------------------------------------------- operator*
// multiplication by a double on the left

inline Vec3 operator* (const double a, const Vec3 & v) {
	return (Vec3 (a * v.xPoint, a * v.yPoint, a * v.zPoint));	
}

// non-inlined non-member function

// ----------------------------------------------------------------------- operator* 
// multiplication by a matrix on the left

Vec3 operator* (const Matrix& mat, const Vec3& v);



#endif