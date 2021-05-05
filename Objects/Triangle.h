#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.h"
#include "../Utilities/Record.h"
#include "../Utilities/Ray.h"
#include "../Utilities/Vec3.h"

class Triangle: public Object {	
	public:

        Point3	v0, v1, v2;
		Normal	norm;
	
		Triangle();   												
				
		Triangle(const Point3& a, const Point3& b, const Point3& c);
	
		Triangle(const Triangle& triangle); 							

		~Triangle();   											

		Triangle& operator= (const Triangle& rhs);
		
		virtual bool getBoundingBox(AABB& outputBox) const override; 
		
		virtual bool intersect(const Ray& ra, double& tmin, Record& recentHits) override;		 					 
		
		virtual bool shadowIntersect(const Ray& ray, double& tmin) const override;  
	
		
};

#endif
