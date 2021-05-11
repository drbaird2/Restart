#include "Phong.h"

Phong::Phong()
	: Material()
{
	ambientBRDF = make_shared<Lambertian>();
	diffuseBRDF = make_shared<Lambertian>();
	specularBRDF = make_shared<GlossySpecular>();
}

Phong::Phong(const Phong& ph)
	:Material(ph)
{
	if (ph.ambientBRDF)
	{
		ambientBRDF = ph.ambientBRDF->clone();
	}
	else
	{
		ambientBRDF = nullptr;
	}

	if (ph.diffuseBRDF)
	{
		diffuseBRDF = ph.diffuseBRDF->clone();
	}
	else
	{
		diffuseBRDF = nullptr;
	}

	if (ph.specularBRDF)
	{
		specularBRDF = ph.specularBRDF->clone();
	}
	else
	{
		diffuseBRDF = nullptr;
	}
}

Phong::~Phong()
{

}

Phong& Phong::operator=(const Phong& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Material::operator=(rhs);

	if (rhs.ambientBRDF)
	{
        ambientBRDF.reset();
		ambientBRDF = rhs.ambientBRDF->clone();
	}

	if (rhs.diffuseBRDF)
	{
        diffuseBRDF.reset();
		diffuseBRDF = rhs.diffuseBRDF->clone();
	}

	if (rhs.specularBRDF)
	{
        specularBRDF.reset();
		specularBRDF = rhs.specularBRDF->clone();
	}

	return *this;
}

shared_ptr<Phong> Phong::clone() const
{
	return make_shared<Phong>(*this);
}

Color Phong::shade(Record& recentHits)
{
	Vec3 wo = -recentHits.sceneRay.dir;
	Color L = ambientBRDF->rho(recentHits, wo) * recentHits.sceneRef.ambientPtr->L(recentHits);
	int numLights = recentHits.sceneRef.lights.size();

	for (int j = 0; j < numLights; j++)
	{
		Vec3 wi = recentHits.sceneRef.lights[j]->getDirection(recentHits);
		float nDotWi = recentHits.sceneNormal * wi;

		if (nDotWi > 0.0)
		{
			bool inShadow = false;

			if (recentHits.sceneRef.lights[j]->getIsShadow())
			{
				Ray ShadowRay(recentHits.sceneHit, wi);
				inShadow = recentHits.sceneRef.lights[j]->inShadow(ShadowRay, recentHits);
			}
			if (!inShadow) {
				L += (diffuseBRDF->func(recentHits, wo, wi) + specularBRDF->func(recentHits, wo, wi))
					* recentHits.sceneRef.lights[j]->L(recentHits) * nDotWi;
			}
		}
	}

	return L;
}

Color Phong::areaLightShade(Record& recentHits)
{
	Vec3 wo = -recentHits.sceneRay.dir;
	Color L = ambientBRDF->rho(recentHits, wo) * recentHits.sceneRef.ambientPtr->L(recentHits);
	int numLights = recentHits.sceneRef.lights.size();

	for (int j = 0; j < numLights; j++)
	{
		Vec3 wi = recentHits.sceneRef.lights[j]->getDirection(recentHits);
		float nDotWi = recentHits.sceneNormal * wi;

		if (nDotWi > 0.0)
		{
			bool inShadow = false;

			if (recentHits.sceneRef.lights[j]->getIsShadow())
			{
				Ray ShadowRay(recentHits.sceneHit, wi);
				inShadow = recentHits.sceneRef.lights[j]->inShadow(ShadowRay, recentHits);
			}
			if (!inShadow) {
				L += (diffuseBRDF->func(recentHits, wo, wi) + specularBRDF->func(recentHits, wo, wi))
					* recentHits.sceneRef.lights[j]->L(recentHits) * recentHits.sceneRef.lights[j]->G(recentHits) *
					nDotWi / recentHits.sceneRef.lights[j]->pdf(recentHits);
			}
		}
	}

	return L;
}

void Phong::SetKa(float ka)
{
	ambientBRDF->setKd(ka);
}

void Phong::SetKd(float kd)
{
	diffuseBRDF->setKd(kd);
}

void Phong::SetKs(float ks)
{
	specularBRDF->SetKs(ks);
}

void Phong::SetExp(float exp)
{
	specularBRDF->SetExp(exp);
}

void Phong::SetCd(const Color c)
{
	ambientBRDF->setCd(c);
	diffuseBRDF->setCd(c);
}

void Phong::SetCd(const double r, const double g, const double b)
{
	ambientBRDF->setCd(r, g, b);
	diffuseBRDF->setCd(r, g, b);
}

void Phong::SetCd(const double c)
{
	ambientBRDF->setCd(c);
	diffuseBRDF->setCd(c);
}

void Phong::SetCs(const Color c)
{
	specularBRDF->SetCs(c);
}

void Phong::SetCs(const double r, const double g, const double b)
{
	specularBRDF->SetCs(r, g, b);
}

void Phong::SetCs(const double c)
{
	specularBRDF->SetCs(c);
}