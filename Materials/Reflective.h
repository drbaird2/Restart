#ifndef __REFLECTIVE__
#define __REFLECTIVE__


#include "Phong.h"
#include "../BRDFs/PerfectSpecular.h"

/*******************************************************************
 * Class - Reflective
 * 
 * For reflective materials like mirrors and metal
 * just requires a perfectspecular component
 * 
 *******************************************************************/
class Reflective: public Phong {	
	public:
	
		Reflective(void);										

		Reflective(const Reflective& rm);						

		Reflective& operator= (const Reflective& rhs);						

		virtual shared_ptr<Reflective> clone(void) const;				

		~Reflective(void);										
		
		void set_kr(const float k);
				
		void set_cr(const Color& c);
		
		void set_cr(const double r, const double g, const double b);
		
		void set_cr(const double c);
		
		virtual Color shade(Record& recentHits);
		
	private:
	
		shared_ptr<PerfectSpecular> reflective_brdf;		
};


// ---------------------------------------------------------------- set_kr

inline void Reflective::set_kr(const float k) {
	reflective_brdf->set_kr(k);
}


// ---------------------------------------------------------------- set_cr

inline void Reflective::set_cr(const Color& c) {
	reflective_brdf->set_cr(c);
	
}


// ---------------------------------------------------------------- set_cr

inline void Reflective::set_cr(const double r, const double g, const double b) {
	reflective_brdf->set_cr(r, g, b);
}


// ---------------------------------------------------------------- set_cr

inline void Reflective::set_cr(const double c) {
	reflective_brdf->set_cr(c);
}

#endif
