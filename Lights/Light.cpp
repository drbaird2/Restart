#include "Light.h"
#include "../Utilities/Constants.h"

Light::Light()
	: isShadow(false)
{

}

Light::Light(const Light& ls)
	: isShadow(ls.isShadow)
{

}

Light::~Light()
{

}

Light& Light::operator=(const Light& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	isShadow = rhs.isShadow;

	return *this;
}

Color Light::L(Record& recentHits)
{
	return black;
}

float Light::G(const Record& recentHits)
{
	return 1.0f;
}

float Light::pdf(const Record& recentHits) const
{
	return 1.0f;
}

bool Light::inShadow(const Ray& ra, const Record& recentHits) const
{
	return false;
}