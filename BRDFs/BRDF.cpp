#include "BRDF.h"
#include "../Utilities/Constants.h"

BRDF::BRDF():
    samplerPtr(nullptr)
{}

BRDF::BRDF(const BRDF& brdf){
	if (brdf.samplerPtr){
		samplerPtr = brdf.samplerPtr->clone();
	}
	else{
		samplerPtr = nullptr;
	}
}

BRDF& BRDF::operator=(const BRDF& rhs)
{
	if (this == &rhs){
		return *this;
	}

	if (samplerPtr){
		samplerPtr.reset();
		samplerPtr = nullptr;
	}

	if (rhs.samplerPtr){
		samplerPtr = rhs.samplerPtr->clone();
	}

	return *this;
}

BRDF::~BRDF(){
	if (samplerPtr)
	{
		samplerPtr.reset();
		samplerPtr = nullptr;
	}
}

shared_ptr<BRDF> BRDF::clone()
{
	return std::make_shared<BRDF>(*this);
}

void BRDF::setSampler(shared_ptr<Sampler> sPtr){
	samplerPtr = sPtr;
	samplerPtr->mapSamplesToHemisphere(1); //for perfect diffuse
}

Color BRDF::func(const Record& recentHits, const Vec3& wo, const Vec3& wi) const{
	return black;
}

Color BRDF::sampleFunc(const Record& recentHits, const Vec3& wo, Vec3& wi) const{
	return black;
}

Color BRDF::sampleFunc(const Record& recentHits, const Vec3& wo, Vec3& wi, float& pdf) const{
	return black;
}

Color BRDF::rho(const Record& recentHits, const Vec3& wo) const{
	return black;
}