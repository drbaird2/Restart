#ifndef BTDF_H
#define BTDF_H

#include <math.h>

#include "../Utilities/Constants.h"
#include "../Utilities/Vec3.h"
#include "../Utilities/Record.h"


/*******************************************************************
 * Class BTDF
 * 
 * Base class for all Bidirectional Tranmittance distribution functions
 * like a BRDF but for the refraction and transmission of light underneath
 * a surface. For transparent materials
 * 
 *******************************************************************/
class BTDF {
	public:
	
		BTDF(void);
		
		BTDF(const BTDF& btdf);
		
		shared_ptr<BTDF> clone(void);
		
		BTDF& operator= (const BTDF& rhs);
		
		virtual ~BTDF(void);
				
		virtual Color func(const Record& recentHits, const Vec3& wo, const Vec3& wi) const;
		
		virtual Color sampleFunc(const Record& recentHits, const Vec3& wo, Vec3& wt) const;
		
		virtual Color rho(const Record& recentHits, const Vec3& wo) const;
};

#endif
