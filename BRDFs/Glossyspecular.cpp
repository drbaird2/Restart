#include "GlossySpecular.h"
#include "../Samplers/MultiJittered.h"
#include "../Utilities/Constants.h"
#include <cmath>


/*******************************************************************
 * Constructors
 * 
 *******************************************************************/
GlossySpecular::GlossySpecular()
	: BRDF()
	, Ks(0.0)
	, Cs(0.0)
	, Exp(1.0)
{
}

GlossySpecular::~GlossySpecular()
{

}

std::shared_ptr<GlossySpecular> GlossySpecular::clone() const
{
	return make_shared<GlossySpecular>(*this);
}


Color GlossySpecular::func(const Record& recentHits, const Vec3& wo, const Vec3& wi) const
{
	Color L;
	float nDotWi = recentHits.sceneNormal * wi;
	Vec3 r(-wi + 2.0 * recentHits.sceneNormal * nDotWi);
	r.unit_vector(); //r is unit vector
	float rDotWo = r * wo;
	
	if (rDotWo > 0.0)
	{
		L = Ks * Cs * pow(rDotWo, Exp);
	}

	return L;
}

/*******************************************************************
 * Sample for getting the Specular component
 * 
 *******************************************************************/
Color GlossySpecular::sampleFunc(const Record& recentHits, const Vec3& wo, Vec3& wi, float& pdf) const
{
	float nDotWo = recentHits.sceneNormal * wo;
	Vec3 r = -wo + 2.0 * recentHits.sceneNormal * nDotWo;

	Vec3 w = r;
	Vec3 u = Vec3(0.00424, 1, 0.00764) ^ w;
	u.unit_vector();
	Vec3 v = u ^ w;

	Point3 sp = samplerPtr->sampleHemisphere();
	wi = sp.xPoint * u + sp.yPoint * v + sp.zPoint * w;

	if (recentHits.sceneNormal * wi < 0.0)
	{
		wi = -sp.xPoint * u - sp.yPoint * v + sp.zPoint * w;
	}

	float phong_lobe = pow(r * wi, Exp);
	pdf = phong_lobe * (recentHits.sceneNormal * wi);

	return Ks * Cs * phong_lobe;
}


Color GlossySpecular::rho(const Record& sr, const Vec3& wo) const
{
	return black;
}

void GlossySpecular::SetKs(const float k)
{
	Ks = k;
}

void GlossySpecular::SetExp(const float exp)
{
	Exp = exp;
}

void GlossySpecular::SetCs(const Color& c)
{
	Cs = c;
}

void GlossySpecular::SetCs(const double r, const double g, const double b)
{
	Cs.red = r;
	Cs.green = g;
	Cs.blue = b;
}

void GlossySpecular::SetCs(const float c)
{
	Cs.red = c;
	Cs.green = c;
	Cs.blue = c;
}

void GlossySpecular::SetSampler(shared_ptr<Sampler> sp, const float exp)
{
	samplerPtr = sp;
	samplerPtr->mapSamplesToHemisphere(exp);
}

void GlossySpecular::SetSamples(const int numSamples, const float exp)
{
	samplerPtr = make_shared<MultiJittered>(numSamples);
	samplerPtr->mapSamplesToHemisphere(exp);
}