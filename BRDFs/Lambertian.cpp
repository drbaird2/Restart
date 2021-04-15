#include "Lambertian.h"
#include "../Utilities/Constants.h"

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

shared_ptr<BRDF> Lambertian::clone() const{
	return move(make_shared<Lambertian>(*this));
}

Color Lambertian::func(const Record& recentHits, const Vec3& wo, const Vec3& wi) const{
	return  cd * kd * invPI;
}

Color Lambertian::sampleFunc(const Record& recentHits, const Vec3& wo, Vec3& wi, float& pdf) const{
	return cd * kd * invPI;
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