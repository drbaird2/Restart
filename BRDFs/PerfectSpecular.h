#ifndef PERFECTSPECULAR_H
#define PERFECTSPECULAR_H

#include "BRDF.h"
#include "../Utilities/Normal.h"

class PerfectSpecular: public BRDF 
{
	public:
	
		PerfectSpecular(void);
		
		~PerfectSpecular(void);
		
		virtual shared_ptr<PerfectSpecular> clone(void) const;
		
		void set_kr(const float k);
		
		void set_cr(const Color& c);
		
		void set_cr(const double r, const double g, const double b);
		
		void set_cr(const double c);
		
		virtual Color func(const Record& recentHits, const Vec3& wo, const Vec3& wi) const;
		
		virtual Color sampleFunc(const Record& recentHits, const Vec3& wo, Vec3& wi) const;
		
		virtual Color sampleFunc(const Record& recentHits, const Vec3& wo, Vec3& wi, float& pdf) const;
		
		virtual Color rho(const Record& recentHits, const Vec3& wo) const;
				
	private:
	
		float		kr;			// reflection coefficient
		Color 	cr;			// the reflection colour
};


// -------------------------------------------------------------- set_kr

inline void PerfectSpecular::set_kr(const float k) {
	kr = k;
}


// -------------------------------------------------------------- set_cr

inline void PerfectSpecular::set_cr(const Color& c) {
	cr = c;
}


// ---------------------------------------------------------------- set_cr

inline void	PerfectSpecular::set_cr(const double r, const double g, const double b) {
	cr.red = r; 
    cr.green = g; 
    cr.blue = b;
}


// ---------------------------------------------------------------- set_cr

inline void	PerfectSpecular::set_cr(const double c) {
	cr.red = c; 
    cr.green = c; 
    cr.blue = c;
}

#endif

