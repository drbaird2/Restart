
#include "Transparent.h"

Transparent::Transparent()
	: Phong()
{
	reflective_brdf = make_shared<PerfectSpecular>();
	specular_btdf = make_shared<PerfectTransmitter>();
}

Transparent::Transparent(const Transparent& tp)
	: Phong(tp)
{
	if (tp.reflective_brdf)
	{
		reflective_brdf = tp.reflective_brdf->clone();
	}
	else
	{
		reflective_brdf = make_shared<PerfectSpecular>();
	}

	if (tp.specular_btdf)
	{
		specular_btdf = tp.specular_btdf->clone();
	}
	else
	{
		specular_btdf = make_shared<PerfectTransmitter>();
	}
}

Transparent::~Transparent()
{
}

Transparent& Transparent::operator=(const Transparent& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Phong::operator=(rhs);

	if (rhs.reflective_brdf)
	{
		reflective_brdf = rhs.reflective_brdf->clone();
	}

	if (rhs.specular_btdf)
	{
		specular_btdf = rhs.specular_btdf->clone();
	}

	return *this;
}

std::shared_ptr<Transparent> Transparent::Clone() const
{
	return std::make_shared<Transparent>(*this);
}

Color Transparent::shade(Record& recentHits)
{
	Color L(Phong::shade(recentHits));

	Vec3 wo = -recentHits.sceneRay.dir;
	Vec3 wi;
	Color fr = reflective_brdf->sampleFunc(recentHits, wo, wi);
	Ray reflected_ray(recentHits.sceneHit, wi);

	if (specular_btdf->tir(recentHits))
	{
		L += recentHits.sceneRef.tracerPtr->traceRay(reflected_ray, recentHits.depth + 1);
	}
	else
	{
		Vec3 wt;
		Color ft = specular_btdf->sampleFunc(recentHits, wo, wt);
		Ray transmitted_ray(recentHits.sceneHit, wt);

		L += fr * recentHits.sceneRef.tracerPtr->traceRay(reflected_ray, recentHits.depth + 1) * fabs(recentHits.sceneNormal * wi);
		L += ft * recentHits.sceneRef.tracerPtr->traceRay(transmitted_ray, recentHits.depth + 1) * fabs(recentHits.sceneNormal * wt);
	}

	return L;
}

