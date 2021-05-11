#ifndef PHONG_H
#define PHONG_H

#include "Material.h"
#include "../BRDFs/Lambertian.h"
#include "../BRDFs/GlossySpecular.h"
#include "../Utilities/Scene.h"

class Phong : public Material
{
public:
	Phong();
	Phong(const Phong& ph);
	virtual ~Phong();
	Phong& operator=(const Phong& rhs);

	std::shared_ptr<Phong> clone() const;

	virtual Color shade(Record& recentHits) override;
	virtual Color areaLightShade(Record& recentHits) override;

	void SetKa(float ka);
	void SetKd(float kd);
	void SetKs(float ks);
	void SetExp(float exp);
	void SetCd(const Color c);
	void SetCd(const double r, const double g, const double b);
	void SetCd(const double c);
	void SetCs(const Color c);
	void SetCs(const double r, const double g, const double b);
	void SetCs(const double c);
protected:
	std::shared_ptr<Lambertian> ambientBRDF;
	std::shared_ptr<Lambertian> diffuseBRDF;
	std::shared_ptr<GlossySpecular> specularBRDF;
};

#endif