// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


// this file contains the definition of the class Point3D

#include <math.h>
#include "Point3.h"


// --------------------------------------------- default constructor

Point3::Point3()
	:xPoint(0), 
    yPoint(0), 
    zPoint(0)
{}


// --------------------------------------------- constructor

Point3::Point3(const double a)
	:xPoint(a), 
    yPoint(a), 
    zPoint(a)
{}

// --------------------------------------------- constructor

Point3::Point3(const double a, const double b, const double c)
	:xPoint(a), 
    yPoint(b), 
    zPoint(c)
{}


// --------------------------------------------- copy constructor

Point3::Point3(const Point3& p)
	:xPoint(p.xPoint), 
    yPoint(p.yPoint), 
    zPoint(p.zPoint)
{}


// --------------------------------------------- destructor

Point3::~Point3() 
{}


// --------------------------------------------- assignment operator

Point3& Point3::operator= (const Point3& rhs) {
	
	if (this == &rhs)
		return (*this);

	xPoint = rhs.xPoint; 
    yPoint = rhs.yPoint; 
    zPoint = rhs.zPoint;

	return (*this);
}



// --------------------------------------------- distance
// distance between two points

double Point3::distance(const Point3& p) const {
	return (sqrt(		(xPoint - p.xPoint) * (xPoint - p.xPoint) 
					+ 	(yPoint - p.yPoint) * (yPoint - p.yPoint)
					+	(zPoint - p.zPoint) * (zPoint - p.zPoint) ));
}


// non-member function

// --------------------------------------------- operator*
// multiplication by a matrix on the left

Point3 operator* (const Matrix& mat, const Point3& p) {
	return (Point3(mat.m[0][0] * p.xPoint + mat.m[0][1] * p.yPoint + mat.m[0][2] * p.zPoint + mat.m[0][3],
					mat.m[1][0] * p.xPoint + mat.m[1][1] * p.yPoint + mat.m[1][2] * p.zPoint + mat.m[1][3],
					mat.m[2][0] * p.xPoint + mat.m[2][1] * p.yPoint + mat.m[2][2] * p.zPoint + mat.m[2][3]));
}

Point3 Point3::operator- (const double a) const{
    return Point3(xPoint - a, yPoint - a, zPoint -a);
}