#include "Lambertian.h"
#include "../Utilities/Constants.h"
#include "../Samplers/Multijittered.h"

Lambertian::Lambertian():
	BRDF(),
	kd(0.0),
	cd(0.0)
{}

Lambertian::Lambertian(const Lambertian& lamb):
	BRDF(lamb),
	kd(lamb.kd),
	cd(lamb.cd)
{}

Lambertian& Lambertian::operator=(const Lambertian& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	BRDF::operator=(rhs);

	kd = rhs.kd;
	cd = rhs.cd;

	return *this;
}

Lambertian::~Lambertian()
{}

shared_ptr<Lambertian> Lambertian::clone(){
	return make_shared<Lambertian>(*this);
}

Color Lambertian::func(const Record& recentHits, const Vec3& wo, const Vec3& wi) const{
	return  cd * kd * invPI;
}

Color Lambertian::sampleFunc(const Record& recentHits, const Vec3& wo, Vec3& wi, float& pdf) const{
	Vec3 w = recentHits.sceneNormal;
	Vec3 v = Vec3(0.0034, 1.0, 0.0071) ^ w;
	v.unit_vector();
	Vec3 u = v ^ w;

	Point3 sp = samplerPtr->sampleHemisphere();
	wi = sp.xPoint * u + sp.yPoint * v + sp.zPoint * w;
	wi.unit_vector();
	pdf = recentHits.sceneNormal * wi * invPI;

	return kd * cd * invPI;
}

Color Lambertian::rho(const Record& recentHits, const Vec3& wo) const{
	return  cd * kd;
}

void Lambertian::setKa(const double ka){
	kd = ka;
}

void Lambertian::setKd(const double kkd){
	kd = kkd;
}

void Lambertian::setCd(const Color& c){
	cd = c;
}

void Lambertian::setCd(const double r, const double g, const double b){
	cd.red = r;
	cd.blue = b;
	cd.green = g;
}

void Lambertian::setCd(const double c){
	cd.red = c;
	cd.green = c;
	cd.blue = c;
}

void Lambertian::setSampler(shared_ptr<Sampler> sp)
{
	samplerPtr = sp;
	samplerPtr->mapSamplesToHemisphere(1);
}

void Lambertian::setSamples(const int numSamples)
{
	samplerPtr = make_shared<MultiJittered>(numSamples);
	samplerPtr->mapSamplesToHemisphere(1);
}