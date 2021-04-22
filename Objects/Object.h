#ifndef OBJECT_H
#define OBJECT_H

#include "../Utilities/Color.h"
#include "../Materials/Material.h"
#include "../Utilities/Record.h"
#include "AABB.h"
#include <memory>

using namespace std;

class Material;
class Record;

class Object{
    public:
        Color                   col;
        shared_ptr<Material>    mat;
        bool                    isShadow;

    public:
        Object();
        Object(const Object& obj);
        virtual ~Object();

        shared_ptr<Object> clone() const;
        
        virtual bool intersect(const Ray& ra, double& t, Record& recentHits);
        virtual bool shadowIntersect(const Ray& ra, double& tmin) const;
        
        Color getColor();
        shared_ptr<Material> getMaterial();
        bool getIsShadow();
        
        void setColor(Color col);
        virtual void setMaterial(shared_ptr<Material> mat);
        void setIsShadow(bool isShadow);

        virtual void addObject(shared_ptr<Object> object_ptr);

        virtual Point3 sample();

        virtual float pdf(Record& recentHits);

        virtual Normal getNormal(const Point3& p);

        virtual AABB getBoundingBox() const;

        Object& operator=(const Object& rhs);


};

inline Object& Object::operator=(const Object& rhs){
    if (this == &rhs)
		return (*this);
		
	col= rhs.col;
	
	if (mat) {
		mat.reset();
		mat = nullptr;
	}

//	if (rhs.mat)
//		mat = rhs.mat->clone();

	//shadows = rhs.shadows;

	return (*this);
}

inline Color Object::getColor(){
    return col;
}

inline shared_ptr<Material> Object::getMaterial(){
    return mat;
}

inline bool Object::getIsShadow(){
    return isShadow;
}

inline void Object::setColor(Color coll){
    col.red = coll.red;
    col.green = coll.green;
    col.blue = coll.blue;
}

inline void Object::setIsShadow(bool isS){
    isShadow = isS;
}

#endif