#include "Vec3.h"
#include "Normal.h"
#include "Point3.h"

Vec3::Vec3():
    xPoint(0),
    yPoint(0),
    zPoint(0)
{}

Vec3::Vec3(double a): 
    xPoint(a), 
    yPoint(a), 
    zPoint(a)							
{}

Vec3::Vec3(double xs, double ys, double zs):
    xPoint(xs),
    yPoint(ys),
    zPoint(zs)
{}

// ---------------------------------------------------------- copy constructor

Vec3::Vec3(const Vec3& v)
	: xPoint(v.xPoint), 
    yPoint(v.yPoint), 
    zPoint(v.zPoint)
{}

// ---------------------------------------------------------- constructor
// constructs a vector from a normal

Vec3::Vec3(const Normal& n)	 
	: xPoint(n.xPoint), 
    yPoint(n.yPoint), 
    zPoint(n.zPoint)
{}

// ---------------------------------------------------------- constructor
// constructs a vector from a point
// this is used in the ConcaveHemisphere hit functions

Vec3::Vec3(const Point3& p)	 
	: xPoint(p.xPoint), yPoint(p.yPoint), zPoint(p.zPoint)
{}

// ---------------------------------------------------------- destructor

Vec3::~Vec3 (void) {}

Vec3& Vec3::operator= (const Vec3& rhs) {
	if (this == &rhs)
		return (*this);

	xPoint = rhs.xPoint; yPoint = rhs.yPoint; zPoint = rhs.zPoint;

	return (*this);
}

// ----------------------------------------------------------- assignment operator
// assign a Normal to a vector

Vec3& Vec3::operator= (const Normal& rhs) {
	xPoint = rhs.xPoint; yPoint = rhs.yPoint; zPoint = rhs.zPoint;
	return (*this);
}

// ---------------------------------------------------------- assignment operator 
// assign a point to a vector

Vec3& Vec3::operator= (const Point3& rhs) {
	xPoint = rhs.xPoint; yPoint = rhs.yPoint; zPoint = rhs.zPoint;
	return (*this);
}

double Vec3::length(void) {
    return sqrt(length_squared());
}

void Vec3::unit_vector(){
    double len = this->length();
    xPoint /= len;
    yPoint /= len;
    zPoint /= len;
}

// non-member function

// ----------------------------------------------------------  operator* 
// multiplication by a matrix on the left

Vec3 operator* (const Matrix& mat, const Vec3& v) {
	return (Point3(mat.m[0][0] * v.xPoint + mat.m[0][1] * v.yPoint + mat.m[0][2] * v.zPoint,
					mat.m[1][0] * v.xPoint + mat.m[1][1] * v.yPoint + mat.m[1][2] * v.zPoint,
					mat.m[2][0] * v.xPoint + mat.m[2][1] * v.yPoint + mat.m[2][2] * v.zPoint));
}
