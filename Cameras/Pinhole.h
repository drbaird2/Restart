#ifndef PINHOLE_H
#define PINHOLE_H

#include "Camera.h"
#include "..//Utilities//Point2.h"

class Scene;

class Pinhole : public Camera{
    public:
        double dist;
	    double zoom;

	    Pinhole();
	    Pinhole(const Pinhole& ph);
	    ~Pinhole();

	/* shared_ptr<Camera> Clone() const override; */

	    Pinhole& operator=(const Pinhole& rhs);

	    void setViewDistance(const double view);
	    void setZoom(const double factor);
	    Vec3 getDirection(const Point2& p) const;
	    void renderScene( Scene& scenePtr) override;
	
};

inline void Pinhole::setViewDistance(double d)
{
	dist = d;
}

inline void Pinhole::setZoom(const double factor)
{
	zoom = factor;
}


#endif