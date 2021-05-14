#include "Vec3.h"
#include "Normal.h"
#include "Point3.h"


/*******************************************************************
 * Constructors
 * 
 * Vec3() - default (0,0,0) vector
 * 
 * Vec3(double a) - construct (a,a,a)
 * 
 * Vec3(double xs, double ys, double zs) - construct vec from x,y,z points
 * 
 * Vec3(Vec3) - copy constructor
 * 
 * Vec3(Normal) - Construct a Vector from a Normal
 * 
 * Vec3(Point3) - Construct a Vector from a Point3
 * 
 *******************************************************************/
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


Vec3::Vec3(const Vec3& v):
	xPoint(v.xPoint), 
    yPoint(v.yPoint), 
    zPoint(v.zPoint)
{}

Vec3::Vec3(const Normal& n):	 
	xPoint(n.xPoint), 
    yPoint(n.yPoint), 
    zPoint(n.zPoint)
{}

Vec3::Vec3(const Point3& p):   
    xPoint(p.xPoint), 
    yPoint(p.yPoint), 
    zPoint(p.zPoint)
{}

Vec3::~Vec3 (void) {}

/*******************************************************************
 * Assignment Opperators
 * 
 * Exists for Vec3 = Normal and Vec3 = Point3
 * 
 *******************************************************************/

Vec3& Vec3::operator= (const Vec3& rhs) {
	if (this == &rhs)
		return (*this);

	xPoint = rhs.xPoint; yPoint = rhs.yPoint; zPoint = rhs.zPoint;

	return (*this);
}

Vec3& Vec3::operator= (const Normal& rhs) {
	xPoint = rhs.xPoint; yPoint = rhs.yPoint; zPoint = rhs.zPoint;
	return (*this);
}

Vec3& Vec3::operator= (const Point3& rhs) {
	xPoint = rhs.xPoint; yPoint = rhs.yPoint; zPoint = rhs.zPoint;
	return (*this);
}

/*******************************************************************
 * length() - returns the length of the current Vector
 * 
 *******************************************************************/
double Vec3::length(void) {
    return sqrt(length_squared());
}

/*******************************************************************
 * unit_vector() - Normalizes the current vector
 * 
 *******************************************************************/
void Vec3::unit_vector(){
    double len = this->length();
    xPoint /= len;
    yPoint /= len;
    zPoint /= len;
}

/*******************************************************************
 * Opperator function for Affine Transformations
 * 
 *******************************************************************/
Vec3 operator* (const Matrix& mat, const Vec3& v) {
	return (Point3(mat.m[0][0] * v.xPoint + mat.m[0][1] * v.yPoint + mat.m[0][2] * v.zPoint,
					mat.m[1][0] * v.xPoint + mat.m[1][1] * v.yPoint + mat.m[1][2] * v.zPoint,
					mat.m[2][0] * v.xPoint + mat.m[2][1] * v.yPoint + mat.m[2][2] * v.zPoint));
}
