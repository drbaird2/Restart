#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;
using std::fabs;

class Vec3{
    public:
        double xPoint, yPoint, zPoint;

    public:
        Vec3();
        Vec3(double x, double y, double z);

        double x() const;
        double y() const;
        double z() const;

        Vec3 operator-() const;
        Vec3 operator+(const Vec3 &v);
        Vec3 operator-(const Vec3 &v);
        Vec3 operator*(const Vec3 &v);
        Vec3 operator*(double t);
        Vec3 operator/(double t);
        
        Vec3& operator+=(const Vec3 &v);
        Vec3& operator*=(const double t);
        Vec3& operator/=(const double t);

        std::ostream& operator<<(std::ostream &out);
        
        double length() const;
        double length_squared() const;


        double dot(const Vec3 &v);
        Vec3 cross(const Vec3 &v);
        Vec3 unit_vector();
};

using Point3 = Vec3;
using Normal = Vec3;

inline Vec3 Vec3::operator-() const{
    return Vec3(-xPoint,-yPoint, -zPoint);
}

inline Vec3 Vec3::operator+(const Vec3 &v){
    return Vec3(xPoint + v.xPoint, yPoint + v.yPoint, zPoint+v.zPoint);
}
inline Vec3 Vec3::operator-(const Vec3 &v){
    return Vec3(xPoint - v.xPoint, yPoint - v.yPoint, zPoint - v.zPoint);
}

inline Vec3 Vec3::operator*(const Vec3 &v){
    return Vec3(xPoint * v.xPoint, yPoint * v.yPoint, zPoint * v.zPoint);
}

inline Vec3 Vec3::operator*(double t){
    return Vec3(xPoint * t, yPoint * t, zPoint * t);
}

inline Vec3 Vec3::operator/(double t){
    return Vec3(xPoint/t, yPoint/t, zPoint/t);
}
        
inline Vec3& Vec3::operator+=(const Vec3 &v){
    xPoint += v.xPoint;
    yPoint += v.yPoint;
    zPoint += v.zPoint;
    return *this;
}

inline Vec3& Vec3::operator*=(const double t){
    xPoint *= t;
    yPoint *= t;
    zPoint *= t;
    return *this;
}

inline Vec3& Vec3::operator/=(const double t){
    return *this *= 1/t;
}

inline std::ostream& Vec3::operator<<(std::ostream &out){
    return out << xPoint << ' ' << yPoint << ' ' << zPoint;
}

#endif