#include "Emissive.h"
#include "../Utilities/Constants.h"

Emissive::Emissive()
	: Material()
	, Ls(0.5)
	, Ce()
{
}

Emissive::Emissive(const Emissive& e)
	: Material(e)
	, Ls(e.Ls)
	, Ce(e.Ce)
{
}

Emissive::~Emissive()
{
}

Emissive& Emissive::operator=(const Emissive& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Material::operator=(rhs);
	Ls = rhs.Ls;
	Ce = rhs.Ce;

	return *this;
}

shared_ptr<Emissive> Emissive::clone() const
{
	return make_shared<Emissive>(*this);
}

void Emissive::setLadiance(const float ls)
{
	Ls = ls;
}

void Emissive::setCe(const Color c)
{
	Ce = c;
}

void Emissive::setCe(const double r, const double g, const double b)
{
	Ce.red = r;
	Ce.green = g;
	Ce.blue = b;
}

void Emissive::setCe(const double c)
{
	Ce.red = c;
	Ce.green = c;
	Ce.blue = c;
}

Color Emissive::shade(Record& recentHits)
{
	return black;
}

Color Emissive::pathShade(Record& recentHits)
{
	if (-recentHits.sceneNormal * recentHits.sceneRay.dir > 0.0)
	{
		return Ce*Ls;
	}
	else
	{
		return black;
	}
}

Color Emissive::globalShade(Record& recentHits)
{
	if (recentHits.depth == 1)
	{
		return black;
	}
	
	if (-recentHits.sceneNormal*recentHits.sceneRay.dir > 0.0)
	{
		return Ce * Ls;
	}
	else
	{
		return black;
	}
}

/*******************************************************************
 * Primary shade function is the area light function
 * Make sure the ray is pointing out to grab the color
 * 
 *******************************************************************/
Color Emissive::areaLightShade(Record& recentHits)
{
	if (-recentHits.sceneNormal*recentHits.sceneRay.dir > 0.0)
	{
		return Ce*Ls;
	}
	else
	{
		return black;
	}
}

Color Emissive::getLe(Record& recentHits) const
{
	return Ce*Ls;
}