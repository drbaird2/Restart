#ifndef BTDF_H
#define BTDF_H

#include <math.h>

#include "../Utilities/Constants.h"
#include "../Utilities/Vec3.h"
#include "../Utilities/Record.h"

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
