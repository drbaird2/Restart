#ifndef POINT2_H
#define POINT2_H

class Point2
{
public:
	double xPoint, yPoint;

	Point2();
	Point2(const double num);
	Point2(const double x, const double y);
	Point2(const Point2& p);
	~Point2();
	
	Point2& operator=(const Point2& rhs);
	Point2 operator*(const double a);
};

#endif