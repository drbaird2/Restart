#ifndef PERFECTSPECULAR_H
#define PERFECTSPECULAR_H

#include "BRDF.h"
#include "../Utilities/Normal.h"


/*******************************************************************
 * Class - PerfectSpecular inherits from BRDF
 * 
 * the brdf for Mirror like reflective surfaces.
 * 
 * Variables
 * 
 * Float kr - the reflection coefficient
 * Color cr - the reflection color
 * 
 *******************************************************************/
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
	
		float		kr;			
		Color 	cr;			
};

/*******************************************************************
 * Setters
 * 
 *******************************************************************/

inline void PerfectSpecular::set_kr(const float k) {
	kr = k;
}




inline void PerfectSpecular::set_cr(const Color& c) {
	cr = c;
}


inline void	PerfectSpecular::set_cr(const double r, const double g, const double b) {
	cr.red = r; 
    cr.green = g; 
    cr.blue = b;
}




inline void	PerfectSpecular::set_cr(const double c) {
	cr.red = c; 
    cr.green = c; 
    cr.blue = c;
}

#endif

