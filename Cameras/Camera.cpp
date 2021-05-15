#include "Camera.h"

Camera::Camera()		
	:	eye(0, 0, 100),
		lookAt(0,0,0),
		upDir(0, 1, 0),
		U(1, 0, 0),
		V(0, 1, 0),
		W(0, 0, 1)
{}

Camera::Camera(const Camera& c)   		
	: 	eye(c.eye),
		lookAt(c.lookAt),
		upDir(c.upDir),
		U(c.U),
		V(c.V),
		W(c.W)
{}

Camera::~Camera()
{}

Camera& Camera::operator= (const Camera& rhs) {
	if (this == &rhs)
		return (*this);
	
	eye				= rhs.eye;
	lookAt			= rhs.lookAt;
	upDir			= rhs.upDir;
	U				= rhs.U;
	V				= rhs.V;
	W				= rhs.W;

	return (*this);
}

/* shared_ptr<Camera> Camera::clone() const { 
    return make_shared<Camera>((*this)); 
} */

/*******************************************************************
 * Compute the UVW base using the eye, lookat, and updir vectors
 * 
 *******************************************************************/

void Camera::ComputeUVW()
{
	W = eye - lookAt;
    W.unit_vector();
	U = upDir^W;
	U.unit_vector();
	V = W^U;

	// process about singularity
	if (eye.xPoint == lookAt.xPoint && eye.zPoint == lookAt.zPoint)
	{
		if (eye.yPoint > lookAt.yPoint)
		{
			U = Vec3(0, 0, 1);
			V = Vec3(1, 0, 0);
			W = Vec3(0, 0, 1);
		}
		else if (eye.yPoint < lookAt.yPoint)
		{
			U = Vec3(1, 0, 0);
			V = Vec3(0, 0, 1);
			W = Vec3(0, -1, 0);
		}
	}
}