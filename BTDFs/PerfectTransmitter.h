#ifndef PERFECTTRANSMITTER_H
#define PERFECTTRANSMITTER_H

// this implements perfect specular transmission for transparent materials

#include "BTDF.h"

class PerfectTransmitter: public BTDF {
	public:
	
		PerfectTransmitter(void);
		
		PerfectTransmitter(const PerfectTransmitter& pt);
		
		virtual shared_ptr<PerfectTransmitter> clone(void);
		
		~PerfectTransmitter(void);
		
		PerfectTransmitter&	operator= (const PerfectTransmitter& rhs);
		
		void set_kt(const float k);
		
		void set_ior(const float eta);

		bool tir(const Record& recentHits) const;
		
		virtual Color func(const Record& recentHits, const Vec3& wo, const Vec3& wi) const;
		
		virtual Color sampleFunc(const Record& recentHits, const Vec3& wo, Vec3& wt) const;
		
		virtual Color rho(const Record& recentHits, const Vec3& wo) const;
				
	private:
	
		float	kt;			// transmission coefficient
		float	ior;		// index of refraction
};


// -------------------------------------------------------------- set_kt

inline void PerfectTransmitter::set_kt(const float k) {
	kt = k;
}

// -------------------------------------------------------------- set_ior

inline void PerfectTransmitter::set_ior(const float eta) {
	ior = eta;
}

#endif
