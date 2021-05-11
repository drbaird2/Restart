#ifndef GLOSSYSPECULAR_H
#define GLOSSYSPECULAR_H

#include "BRDF.h"

class GlossySpecular :public BRDF
{
public:
	GlossySpecular();
	~GlossySpecular();

	shared_ptr<GlossySpecular> clone() const;
	Color func(const Record& recentHits, const Vec3& wo, const Vec3& wi) const override;
	Color sampleFunc(const Record& recentHits, const Vec3& wo, Vec3& wi, float& pdf) const override;
	Color rho(const Record& recentHits, const Vec3& wo) const;

	void SetKs(const float k);
	void SetExp(const float exp);
	void SetCs(const Color& c);
	void SetCs(const double r, const double g, const double b);
	void SetCs(const float c);

	void SetSampler(shared_ptr<Sampler> sp, const float exp);
	void SetSamples(const int numSamples, const float exp);
private:
	float Ks;
	Color Cs;
	float Exp;
};

#endif