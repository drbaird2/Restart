#ifndef NORMAL_H
#define NORMAL_H

#include "Matrix.h"
#include "Vec3.h"
#include "Point3.h"

class Normal {	
	public:
	
		double	xPoint, yPoint, zPoint;
				
	public:
	
		Normal(void);										// default constructor
		Normal(double a);									// constructor
		Normal(double x, double y, double z);			// constructor
		Normal(const Normal& n); 							// copy constructor
		Normal(const Vec3& v);							// constructs a normal from a vector
		
		~Normal(void);										// destructor

		Normal& 											// assignment operator
		operator= (const Normal& rhs); 	
		
		Normal& 											// assignment of a vector to a normal
		operator= (const Vec3& rhs);
		
		Normal& 											// assignment of a point to a normal
		operator= (const Point3& rhs);
		
		Normal 												// unary minus
		operator- (void) const;	
		
		Normal 												// addition
		operator+ (const Normal& n) const;
		
		Normal& 											// compound addition
		operator+= (const Normal& n);
		
		double
		operator* (const Vec3& v) const;				// dot product with a vector on the right
		
		Normal 												// multiplication by a double on the right
		operator* (const double a) const;
				
		void 												// convert normal to a unit normal
		normalize(void); 									 		
};



// inlined member functions

// ----------------------------------------------------------------------- operator-
// unary minus

inline Normal Normal::operator- (void) const {
	return (Normal(-xPoint, -yPoint, -zPoint));
}


// ----------------------------------------------------------------------- operator+
// addition of two normals

inline Normal Normal::operator+ (const Normal& n) const {
	return (Normal(xPoint + n.xPoint, yPoint + n.yPoint, zPoint + n.zPoint));
}


// ----------------------------------------------------------------------- addition
// compound addition of two normals

inline Normal& Normal::operator+= (const Normal& n) {
	xPoint += n.xPoint; 
    yPoint += n.yPoint; 
    zPoint += n.zPoint;
    return (*this);
}


// ----------------------------------------------------------------------- operator*
// dot product of a normal on the left and a vector on the right

inline double Normal::operator* (const Vec3& v) const {
	return (xPoint * v.xPoint + yPoint * v.yPoint + zPoint * v.zPoint);
}


// ----------------------------------------------------------------------- operator*
// multiplication by a double on the right

inline Normal Normal::operator* (const double a) const {
	return (Normal(xPoint * a, yPoint * a, zPoint * a));
}



// inlined non-member functions

// ----------------------------------------------------------------------- operator*
// multiplication by a double on the left

Normal operator* (const double a, const Normal& n);

inline Normal operator*(const double f, const Normal& n) {
	return (Normal(f * n.xPoint, f * n.yPoint,f * n.zPoint));
}


// ----------------------------------------------------------------------- operator+
// addition of a vector on the left to return a vector 

Vec3 operator+ (const Vec3& v, const Normal& n);

inline Vec3 operator+ (const Vec3& v, const Normal& n) {	
	return (Vec3(v.xPoint + n.xPoint, v.yPoint + n.yPoint, v.zPoint + n.zPoint));
}	


// ----------------------------------------------------------------------- operator-
// subtraction of a normal from a vector to return a vector

Vec3 operator- (const Vec3&, const Normal& n);

inline Vec3 operator- (const Vec3& v, const Normal& n) {
	return (Vec3(v.xPoint - n.xPoint, v.yPoint - n.yPoint, v.zPoint - n.zPoint));
}


// ----------------------------------------------------------------------- operator*
// dot product of a vector on the left and a normal on the right

double operator* (const Vec3& v, const Normal& n);


inline double operator* (const Vec3& v, const Normal& n) {
	return (v.xPoint * n.xPoint + v.yPoint * n.yPoint + v.zPoint * n.zPoint);     
}

// non-inlined non-member function

// ----------------------------------------------------------------------- operator*
// multiplication by a matrix on the left

Normal 												// prototype							
operator* (const Matrix& mat, const Normal& n);



#endif