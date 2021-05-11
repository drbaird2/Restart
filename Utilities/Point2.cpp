#include "Point2.h"

Point2::Point2()
	: xPoint(0.0)
	, yPoint(0.0)
{}

Point2::Point2(const float num)
	: xPoint(num)
	, yPoint(num)
{

}

Point2::Point2(const float x, const float y)
	: xPoint(x)
	, yPoint(y)
{

}

Point2::Point2(const Point2& p)
	: xPoint(p.xPoint)
	, yPoint(p.yPoint)
{

}

Point2::~Point2()
{

}

Point2& Point2::operator=(const Point2& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	xPoint = rhs.xPoint;
	yPoint = rhs.yPoint;

	return *this;
}
