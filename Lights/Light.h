#ifndef LIGHT_H
#define LIGHT_H

#include "../Utilities/Color.h"
#include "../Utilities/Ray.h"
#include "../Utilities/Record.h"
#include <memory>

class Record;

class Light{
    public:
        bool isShadow;

	Light();
	Light(const Light& ls);
	~Light();

	Light& operator=(const Light& rhs);

	virtual Vec3 getDirection(Record& recentHits) = 0;
	virtual Color L(Record& recentHits);
	virtual float G(const Record& recentHits) const;
	virtual float pdf(const Record& recentHits) const;
	virtual bool inShadow(const Ray& ra, const Record& recentHits) const;

	bool getIsShadow() { return isShadow; }
	void setIsShadow(bool shadow) { isShadow = shadow; }

};

#endif