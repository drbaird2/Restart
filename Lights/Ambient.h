#ifndef AMBIENT_H
#define AMBIENT_H

#include "Light.h"

class Ambient : public Light{
    public:
        double ls;
	    Color col;
	    
        Ambient();
	    Ambient(const Ambient& a);
	    ~Ambient();
	    Ambient& operator=(const Ambient& rhs);

	    shared_ptr<Ambient> clone() const;
	    Vec3 getDirection(Record& recentHits) override;
	    Color L(Record& recentHits) override;
	
	void setScaleRadiance(const double b);
	void setColor(const double c);
	void setColor(const Color& c);
	void setColor(const double r, const double g, const double b);
	
};
#endif