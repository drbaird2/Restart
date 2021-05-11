#ifndef CAMERA_H
#define CAMERA_H

#include <memory>
#include "..//Utilities//Scene.h"
#include "..//Utilities//Vec3.h"
#include "../Utilities/Point3.h"

class Camera {
    public:
        Point3 eye, lookAt;
	    Vec3 U, V, W;
        Vec3 upDir;

	    Camera();
	    Camera(const Camera& camera);
	    virtual ~Camera();

       /*  virtual shared_ptr<Camera> clone() const; */

        void setEye(const Point3& p);
	    void setEye(const double x, const double y, const double z);
	    void setLookAt(const Point3& look);
	    void setLookAt(const double x, const double y, const double z);
	    void setUpVector(const Vec3& up);
	    void setUpVector(const double x, const double y, const double z);

        void ComputeUVW();

        virtual void renderScene( Scene& scenePtr) = 0;

	    Camera& operator=(const Camera& camera);
};

inline void Camera::setEye(const Point3& p){
    eye = p;
}

inline void Camera::setEye(const double x, const double y, const double z){
    eye = Point3(x,y,z);
}

inline void Camera::setLookAt(const Point3& at){
    lookAt = at;
}

inline void Camera::setLookAt(const double x, const double y, const double z){
    lookAt = Point3(x,y,z);
}

inline void Camera::setUpVector(const Vec3& up){
    upDir = up;
}

inline void Camera::setUpVector(const double x, const double y, const double z){
    upDir = Vec3(x,y,z);
}

#endif
