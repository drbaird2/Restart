#include "Ambient.h"

Ambient::Ambient()
	: Light(),
	 ls(1.0),
	col(1.0)
{

}

Ambient::Ambient(const Ambient& a)
	: Light(a)
	, ls(a.ls)
	, col(a.col)
{
}

Ambient::~Ambient()
{

}

Ambient& Ambient::operator=(const Ambient& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Light::operator=(rhs);

	ls = rhs.ls;
	col = rhs.col;

	return *this;
}

shared_ptr<Ambient> Ambient::clone() const
{
	return std::make_shared<Ambient>(*this);
}

Vec3 Ambient::getDirection(Record& recentHits)
{
	return Vec3(0.0,0.0,0.0);
}

Color Ambient::L(Record& recentHits)
{
	return col * ls;
}

void Ambient::setScaleRadiance(const double b)
{
	ls = b;
}

void Ambient::setColor(const double c)
{
	col.red = c;
	col.green = c;
	col.blue = c;
}

void Ambient::setColor(const Color& c)
{
	col = c;
}

void Ambient::setColor(const double r, const double g, const double b)
{
	col.red = r;
	col.green = g;
	col.blue = b;
}