#include "Pinhole.h"
#include "..//Utilities//Color.h"
#include "..//Utilities//Ray.h"
#include "..//Utilities//Viewplane.h"


Pinhole::Pinhole()
	: Camera()
	, dist(500)
	, zoom(1.0)
{

}

Pinhole::Pinhole(const Pinhole& c)
	: Camera(c)
	, dist(c.dist)
	, zoom(c.zoom)
{

}

Pinhole::~Pinhole()
{

}

/* std::shared_ptr<Camera> Pinhole::Clone() const
{
	return std::move(std::make_shared<Pinhole>(*this));
} */

Pinhole& Pinhole::operator=(const Pinhole& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Camera::operator=(rhs);

	dist = rhs.dist;
	zoom = rhs.zoom;

	return *this;
}

void Pinhole::renderScene( Scene& scenePtr)
{
	Color L;
	Viewplane vp(scenePtr.vp);
	Ray ra;
	int depth = 0; //recursion depth
	Point2 sp;
	Point2 pp;

	vp.ps /= zoom;
	ra.orig = eye;

	cout << "P3\n" << vp.vres << " " << vp.hres << "\n255\n";

	for (int r = 0; r < vp.vres; r++)
	{
		cerr << "\rRendering: Row " << r << ' ' << std::flush;
		for (int c = 0; c < vp.hres; c++)
		{
			L = black;

			for (int j = 0; j < vp.numSamples; j++)
			{
				sp = vp.samplerPtr->sampleUnitSquare();
				pp.xPoint = vp.ps * (c - 0.5 * vp.hres + sp.xPoint);
				pp.yPoint = vp.ps * (r - 0.5 * vp.vres + sp.yPoint);
				ra.dir = getDirection(pp);
				// TraceRay output black pixel now
				// so if you run any programs, image is all black.
				// if you use TraceRay(ray);, you can output ideal images. 
				L += scenePtr.tracerPtr->traceRay(ra);
			}
			//L /= vp.numSamples;
			
			scenePtr.DisplayPixel(r, c, L);
		}
	}
}



Vec3 Pinhole::getDirection(const Point2& p) const
{
	Vec3 dir = p.xPoint * U + p.yPoint * V - dist * W;
	dir.unit_vector();
	return dir;
}