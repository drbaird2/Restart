#ifndef MATERIAL_H
#define MATERIAL_H

//#include "scene.h"		
#include "../Utilities/Color.h"
#include "../Utilities/Record.h"
#include <memory>

using namespace std;

class Record;

class Material {	
	public:
	
		Material();								
		Material(const Material& material);
        virtual ~Material();

		shared_ptr<Material> clone() const;
				
		virtual Color shade(Record& recentHits);
		virtual Color areaLightShade(Record& recentHits);
		virtual Color pathShade(Record& recentHits);
		virtual Color globalShade(Record& recentHits);
		virtual Color getLe(Record& recentHits) const;	
	
		Material& operator= (const Material& rhs);						
};

inline Material& Material::operator=(const Material& rhs){
    if(this == &rhs){
        return *this;
    }
    return *this;
}

#endif
