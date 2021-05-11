

#include "Normal.h"


// ---------------------------------------------------------- default constructor

Normal::Normal(void)
	 : xPoint(0.0), 
     yPoint(0.0), 
     zPoint(0.0)							
{}


// ---------------------------------------------------------- constructor

Normal::Normal(double a)
	 : xPoint(a), yPoint(a), zPoint(a)							
{}


// ---------------------------------------------------------- constructor

Normal::Normal(double x, double y, double z)	 
	: xPoint(x), yPoint(y), zPoint(z)
{}


// ---------------------------------------------------------- copy constructor

Normal::Normal(const Normal& n)
	: xPoint(n.xPoint), yPoint(n.yPoint), zPoint(n.zPoint)
{}


// ---------------------------------------------------------- constructor
// construct a normal from a vector

Normal::Normal(const Vec3& v)	 
	: xPoint(v.xPoint), yPoint(v.yPoint), zPoint(v.zPoint)  
{}


// ---------------------------------------------------------- destructor

Normal::~Normal (void) 							
{}


// ----------------------------------------------------------- operator=
// assignment operator

Normal& Normal::operator= (const Normal& rhs) {
	if (this == &rhs)
		return (*this);

	xPoint = rhs.xPoint; 
    yPoint = rhs.yPoint; 
    zPoint = rhs.zPoint;

	return (*this);
}


// ------------------------------------------------------------ operator=
// assignment of a vector to a normal

Normal& Normal::operator= (const Vec3& rhs) {
	xPoint = rhs.xPoint; 
    yPoint = rhs.yPoint; 
    zPoint = rhs.zPoint;
	return (*this);
}


// ------------------------------------------------------------ operator=
// assignment of a point to a normal

Normal& Normal::operator= (const Point3& rhs) {		
	xPoint = rhs.xPoint; 
    yPoint = rhs.yPoint; 
    zPoint = rhs.zPoint;
	return (*this);
}


// ------------------------------------------------------------ normalize

void Normal::normalize(void) {	
	double length = sqrt(xPoint * xPoint + yPoint * yPoint + zPoint * zPoint);
	xPoint /= length; 
    yPoint /= length; 
    zPoint /= length;
}


// non-member function definition

// ---------------------------------------------------------- operator*
// multiplication by a matrix on the left

// a normal is transformed by multiplying it on the left by the transpose of the upper left 3 x 3
// partition of the inverse transformation matrix

Normal operator* (const Matrix& mat, const Normal& n) {
	return (Normal(	mat.m[0][0] * n.xPoint + mat.m[1][0] * n.yPoint + mat.m[2][0] * n.zPoint,
					mat.m[0][1] * n.xPoint + mat.m[1][1] * n.yPoint + mat.m[2][1] * n.zPoint,
					mat.m[0][2] * n.xPoint + mat.m[1][2] * n.yPoint + mat.m[2][2] * n.zPoint));
}