

#include "Orthographic.h"
#include "../Utilities/Color.h"
#include "../Utilities/Point2.h"
#include "..//Utilities//Viewplane.h"

#include <random>

Orthographic::Orthographic()
	: Camera()
	, zWindow(100.0)
{}

Orthographic::Orthographic(const Orthographic& og)
	: Camera(og)
	, zWindow(og.zWindow)
{}

Orthographic::~Orthographic()
{}

/* std::shared_ptr<Camera> Orthographic::Clone() const
{
	return std::move(std::make_shared<Camera>(*this));
} */

Orthographic& Orthographic::operator=(const Orthographic& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Camera::operator=(rhs);

	zWindow = rhs.zWindow;

	return *this;
}

void Orthographic::setZWindow(const double zw)
{
	zWindow = zw;
}

void Orthographic::renderScene(Scene& scenePtr)
{
	Color pixelColor;
	Viewplane vp(scenePtr.vp);
	Ray ra;
	Point2 pp; //sample point in [0,1] x [0,1]
	Point2 sp; //sample point on a pixel

	ra.dir = Vec3(0, 0, -1);

	//random
	random_device rd;
	mt19937 mt(rd());
	uniform_real_distribution<float> floatRand(0.0f, 1.0f);

	cout << "P3\n" << vp.vres << " " << vp.hres << "\n255\n";
	for (int r = 0; r < vp.vres; r++) //up
	{
		cerr << "\rRendering: Row " << r << ' ' << std::flush;
		for (int c = 0; c <= vp.hres; c++) //across
		{
			pixelColor = black;

			for (int j = 0; j < vp.numSamples; j++)
			{
				//sp = vp.samplerPtr->sampleUnitSquare();
				pp.xPoint = vp.ps * (c - 0.5 * vp.hres + sp.xPoint);
				pp.yPoint = vp.ps * (r - 0.5 * vp.vres + sp.yPoint);
				ra.orig = Point3(pp.xPoint, pp.yPoint, zWindow);
				pixelColor += scenePtr.tracerPtr->traceRay(ra);
			}

			pixelColor /= vp.numSamples;
			scenePtr.DisplayPixel(r, c, pixelColor);
		}
	}
}