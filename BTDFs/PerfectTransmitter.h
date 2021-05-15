#ifndef PERFECTTRANSMITTER_H
#define PERFECTTRANSMITTER_H


#include "BTDF.h"

/*******************************************************************
 * Class PerfectTransmitter - inherits from BTDF
 * 
 * A BTDF that is for completely transparent matterials like glass
 * and air
 * 
 * Variables
 * 
 * float kt - Transmission coefficient
 * float ior - index of refraction (Air -1, Glass - 1.3 to 1.7, Diamond 2.4)
 * 
 *******************************************************************/

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
	
		float	kt;			
		float	ior;		
};

/*******************************************************************
 * Setters
 * 
 *******************************************************************/

inline void PerfectTransmitter::set_kt(const float k) {
	kt = k;
}


inline void PerfectTransmitter::set_ior(const float eta) {
	ior = eta;
}

#endif
