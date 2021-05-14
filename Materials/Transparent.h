#ifndef TRANSPARENT_H
#define TRANSPARENT_H

#include "Phong.h"
#include "../BRDFs/PerfectSpecular.h"
#include "../BTDFs/PerfectTransmitter.h"

class Transparent: public Phong {	
	public:

	Transparent();
	Transparent(const Transparent& tp);
	~Transparent();
	Transparent& operator=(const Transparent& rhs);

	shared_ptr<Transparent> Clone() const;

	virtual Color shade(Record& recentHits);

    void SetIor(float ior);
	void SetKr(float kr);
	void SetKt(float kt);	

	public:

		shared_ptr<PerfectSpecular>     reflective_brdf;
		shared_ptr<PerfectTransmitter>  specular_btdf;	
};

inline void Transparent::SetIor(float ior)
{
	specular_btdf->set_ior(ior);
}

inline void Transparent::SetKr(float kr)
{
	reflective_brdf->set_kr(kr);
}

inline void Transparent::SetKt(float kt)
{
	specular_btdf->set_kt(kt);
}

#endif