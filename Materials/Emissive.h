#ifndef EMISSIVE_H
#define EMISSIVE_H

#include "Material.h"

class Emissive : public Material
{
public:
	Emissive();
	Emissive(const Emissive& e);
	~Emissive();
	Emissive& operator=(const Emissive& rhs);

	shared_ptr<Emissive> clone() const;

	void setLadiance(const float ls);
	void setCe(const Color c);
	void setCe(const double r, const double g, const double b);
	void setCe(const double c);
	Color shade(Record& recentHits) override;
	Color pathShade(Record& recentHits) override;
	Color globalShade(Record& recentHits) override;
	Color areaLightShade(Record& recentHits) override;
	Color getLe(Record& recentHits) const override;
public:
	float Ls; //radiance scaling vector
	Color Ce; //color
};

#endif