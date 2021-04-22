#include "Matte.h"

Matte::Matte(): 
    Material()
{
	ambientBRDF = make_shared<Lambertian>();
	diffuseBRDF = make_shared<Lambertian>();
}

Matte::Matte(const Matte& m):
    Material(m)
{
	if (m.ambientBRDF)
	{
		ambientBRDF = m.ambientBRDF->clone();
	}
	else
	{
		ambientBRDF = nullptr;
	}

	if (m.diffuseBRDF)
	{
		diffuseBRDF = m.diffuseBRDF->clone();
	}
	else
	{
		diffuseBRDF = nullptr;
	}
}

Matte::~Matte()
{
	if (ambientBRDF)
	{
		ambientBRDF.reset();
	}

	if (diffuseBRDF)
	{
		diffuseBRDF.reset();
	}
}

Matte& Matte::operator=(const Matte& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Material::operator=(rhs);

	if (ambientBRDF)
	{
		ambientBRDF.reset();
		ambientBRDF = nullptr;
	}

	if (rhs.ambientBRDF)
	{
		ambientBRDF = rhs.ambientBRDF->clone();
	}

	if (diffuseBRDF)
	{
		diffuseBRDF.reset();
		diffuseBRDF = nullptr;
	}

	if (rhs.diffuseBRDF)
	{
		diffuseBRDF = rhs.diffuseBRDF->clone();
	}

	return *this;
}

shared_ptr<Matte> Matte::clone() const{
	return make_shared<Matte>(*this);
}

void Matte::setKa(const float k){
	ambientBRDF->setKa(k);
}

void Matte::setKd(const float k){
	diffuseBRDF->setKd(k);
}

void Matte::setCd(const Color c){
	ambientBRDF->setCd(c);
	diffuseBRDF->setCd(c);
}

void Matte::setCd(const double r, const double g, const double b){
	ambientBRDF->setCd(r, g, b);
	diffuseBRDF->setCd(r, g, b);
}

void Matte::setCd(const float c){
	ambientBRDF->setCd(c);
	diffuseBRDF->setCd(c);
}

void Matte::setSampler(shared_ptr<Sampler> sp){
	diffuseBRDF->setSampler(sp);
}

void Matte::setSamples(const int numSamples){
	diffuseBRDF->setSamples(numSamples);
}

Color Matte::shade(Record& recentHits)
{
	Vec3 wo = -recentHits.sceneRay.dir;
	Color L = ambientBRDF->rho(recentHits, wo) * recentHits.sceneRef.ambientPtr->L(recentHits);
	int numLights = recentHits.sceneRef.lights.size();

	for (int j = 0; j < numLights; j++)
	{
		Vec3 wi = recentHits.sceneRef.lights[j]->getDirection(recentHits);
		float nDotWi = recentHits.sceneNormal.dot(wi);

		if (nDotWi > 0.0)
		{
			bool inShadow = false;

			if (recentHits.sceneRef.lights[j]->getIsShadow())
			{
				Ray shadowRay(recentHits.sceneHit, wi);
				inShadow = recentHits.sceneRef.lights[j]->inShadow(shadowRay, recentHits);
			}
			if (!inShadow)
			{
				L += diffuseBRDF->func(recentHits, wo, wi) * recentHits.sceneRef.lights[j]->L(recentHits) * nDotWi;
			}
		}
	}

	return L;
}

Color Matte::pathShade(Record& recentHits){
	Vec3 wi;
	Vec3 wo = -recentHits.sceneRay.dir;
	float pdf;
	Color f = diffuseBRDF->sampleFunc(recentHits, wo, wi, pdf);
	float nDotWi = recentHits.sceneNormal.dot(wi);
	Ray reflected_ray(recentHits.sceneHit, wi);

	return (f * recentHits.sceneRef.tracerPtr->traceRay(reflected_ray, recentHits.depth + 1) * nDotWi / pdf);
}

Color Matte::globalShade(Record& recentHits)
{
	Color L;
	
	if (recentHits.depth == 0)
	{
		L = areaLightShade(recentHits);
	}

	Vec3 wi;
	Vec3 wo = -recentHits.sceneRay.dir;
	float pdf;
	Color f = diffuseBRDF->sampleFunc(recentHits, wo, wi, pdf);
	float nDotWi = recentHits.sceneNormal.dot(wi);
	Ray reflected_ray(recentHits.sceneHit, wi);

	L += (f * recentHits.sceneRef.tracerPtr->traceRay(reflected_ray, recentHits.depth + 1) * nDotWi / pdf);

	return L;
}

Color Matte::areaLightShade(Record& recentHits)
{
	Vec3 wo = -recentHits.sceneRay.dir;
	Color L = ambientBRDF->rho(recentHits, wo) * recentHits.sceneRef.ambientPtr->L(recentHits);
	int numLights = recentHits.sceneRef.lights.size();

	for (int j = 0; j < numLights; j++)
	{
		Vec3 wi = recentHits.sceneRef.lights[j]->getDirection(recentHits);
		float nDotWi = recentHits.sceneNormal.dot(wi);
		if (nDotWi > 0.0)
		{
			bool inShadow = false;
			if (recentHits.sceneRef.lights[j]->getIsShadow())
			{
				Ray shadowRay(recentHits.sceneHit, wi);
				inShadow = recentHits.sceneRef.lights[j]->inShadow(shadowRay, recentHits);
			}

			if (!inShadow)
			{
				L += diffuseBRDF->func(recentHits, wo, wi) * recentHits.sceneRef.lights[j]->L(recentHits)
					* recentHits.sceneRef.lights[j]->G(recentHits) * nDotWi /
					recentHits.sceneRef.lights[j]->pdf(recentHits);
			}
		}
	}

	return L;
}