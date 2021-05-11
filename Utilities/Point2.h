#ifndef POINT2_H
#define POINT2_H

class Point2{
public:
	float xPoint, yPoint;

	Point2();
	Point2(const float num);
	Point2(const float x, const float y);
	Point2(const Point2& p);
	~Point2();
	
	Point2& operator=(const Point2& rhs);
	Point2 operator*(const float a);
};

// multiplication by a float on the right

inline Point2 Point2::operator* (const float a) {
	return (Point2(xPoint * a, yPoint * a));
}

#endif