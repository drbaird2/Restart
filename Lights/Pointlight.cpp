#include "PointLight.h"

PointLight::PointLight()
	: Light()
	, ls(1.0)
	, col(1.0)
	, location(0, 0, 0)
{

}

PointLight::PointLight(const PointLight& pl)
	: Light(pl)
	, ls(pl.ls)
	, col(pl.col)
	, location(pl.location)
{

}

PointLight::~PointLight()
{

}

PointLight& PointLight::operator=(const PointLight& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Light::operator=(rhs);

	ls = rhs.ls;
	col = rhs.col;
	location = rhs.location;

	return *this;
}

shared_ptr<PointLight> PointLight::clone() const
{
	return std::make_shared<PointLight>(*this);
}

void PointLight::setScaleRadiance(const double b)
{
	ls = b;
}

void PointLight::setColor(const double c)
{
	col.red = c;
	col.blue = c;
	col.green = c;
}

void PointLight::setColor(const Color& c)
{
	col = c;
}

void PointLight::setColor(const double r, const double g, const double b)
{
	col.red = r;
	col.green = g;
	col.blue = b;
}

void PointLight::setLocation(Vec3 d)
{
	location = d;
}

void PointLight::setLocation(double dx, double dy, double dz)
{
	location.xPoint = dx;
	location.yPoint = dy;
	location.zPoint = dz;
}

Vec3 PointLight::getDirection(Record& recentHits)
{
    Vec3 newdir = (location - recentHits.sceneHit);
    newdir.unit_vector();
	return newdir;
}

Color PointLight::L(Record& recentHits)
{
	return col * ls;
}

bool PointLight::inShadow(const Ray& ra, const Record& recentHits) const
{
	double t;
	int numObjects = recentHits.sceneRef.objects.size();
	double dist = sqrt((pow(location.xPoint - ra.orig.xPoint, 2) 
                        + pow(location.yPoint - ra.orig.yPoint, 2) 
                        + pow(location.zPoint - ra.orig.zPoint, 2)));

	for (int j = 0; j < numObjects; j++)
	{
		if (recentHits.sceneRef.objects[j]->shadowIntersect(ra,t) && t< dist)
		{
			return true;
		}
	}
	return false;
}