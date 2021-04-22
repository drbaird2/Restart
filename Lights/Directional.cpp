#include "Directional.h"

Directional::Directional()
	: Light()
	, ls(1.0)
	, col(1.0)
	, dir(0, 1, 0)
{

}

Directional::Directional(const Directional& dl)
	: Light(dl)
	, ls(dl.ls)
	, col(dl.col)
	, dir(dl.dir)
{

}

Directional::~Directional()
{

}

Directional& Directional::operator=(const Directional& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Light::operator=(rhs);

	ls = rhs.ls;
	col = rhs.col;
	dir = rhs.dir;

	return *this;
}

std::shared_ptr<Directional> Directional::clone() const
{
	return make_shared<Directional>(*this);
}

void Directional::setScaleRadiance(const double b)
{
	ls = b;
}

void Directional::setColor(const double c)
{
	col.red = c;
	col.green = c;
	col.blue = c;
}

void Directional::setColor(const Color& c)
{
	col = c;
}

void Directional::setColor(const double r, const double g, const double b)
{
	col.red = r;
	col.green = g;
	col.blue = b;
}

void Directional::setDirection(Vec3 d)
{
	dir = d;
	dir.unit_vector();
}

void Directional::setDirection(double dx, double dy, double dz)
{
	dir.xPoint = dx;
	dir.yPoint = dy;
	dir.zPoint = dz;
	dir.unit_vector();
}

Vec3 Directional::getDirection(Record& recentHits)
{
	dir.unit_vector();
	return dir;
}

Color Directional::L(Record& recentHits)
{
	return col * ls;
}

bool Directional::inShadow(const Ray& ra, const Record& recentHits) const
{
	double t;
	int numObjects = recentHits.sceneRef.objects.size();

	for (int j = 0; j < numObjects; j++)
	{
		if (!recentHits.sceneRef.objects[j]->getIsShadow())
		{
			continue;
		}

		if (recentHits.sceneRef.objects[j]->shadowIntersect(ra, t))
		{
			return true;
		}
	}
	return false;
}