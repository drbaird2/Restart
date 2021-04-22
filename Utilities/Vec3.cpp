#include "Vec3.h"

Vec3::Vec3():
    xPoint(0),
    yPoint(0),
    zPoint(0)
{}

Vec3::Vec3(double xs, double ys, double zs):
    xPoint(xs),
    yPoint(ys),
    zPoint(zs)
{}

double Vec3::x() const{
    return xPoint;
}

double Vec3::y() const{
    return yPoint;
}

double Vec3::z() const{
    return zPoint;
}

double Vec3::length() const{
    return sqrt(length_squared());
}

double Vec3::length_squared() const{
    return xPoint*xPoint + yPoint*yPoint + zPoint*zPoint;
}

double Vec3::dot(const Vec3 &v){
    return xPoint*v.xPoint + yPoint*v.yPoint + zPoint*v.zPoint;
}

Vec3 Vec3::cross(const Vec3 &v){
    return Vec3(yPoint * v.zPoint - zPoint * v.yPoint,
                zPoint * v.xPoint - xPoint * v.zPoint,
                xPoint * v.yPoint - yPoint * v.xPoint);
}

void Vec3::unit_vector(){
    xPoint = xPoint / this->length();
    yPoint = yPoint / this->length();
    zPoint = zPoint / this->length();
}

