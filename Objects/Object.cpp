#include "Object.h"

Object::Object():
    col(),
    mat(nullptr),
    isShadow(true)
{}

Object::Object(const Object& obj):
    col(obj.col)
{}

Object::~Object()
{}

shared_ptr<Object> Object::clone() const{
    return make_shared<Object>(*this);
}

bool Object::intersect(const Ray& ra, double& t, Record& recentHits){
    return false;
}

bool Object::shadowIntersect(const Ray& ra, double& tmin) const{
    return false;
}

void Object::setMaterial(shared_ptr<Material> matt){
    if (matt){
		mat.reset();
		mat = nullptr;
	}
	mat = matt;
}

void Object::addObject(shared_ptr<Object> object_ptr){
}

Point3 Object::sample(){
    return Point3();
}

float Object::pdf(Record& recentHits){
    return 1.0f;
}

Normal Object::getNormal(const Point3& p){
    return Normal();
}