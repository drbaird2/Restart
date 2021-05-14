#include "Viewplane.h"

/*******************************************************************
 * Constructors
 * 
 * Default is a resolution of 400 by 400
 *******************************************************************/

Viewplane::Viewplane():
    hres(400), 
	vres(400),
	pixelSize(1.0),
    numSamples(1),
    samplerPtr(nullptr),
    maxDepth(0)
{}

Viewplane::Viewplane(const Viewplane& vp):
    hres(vp.hres), 
	vres(vp.vres),
	pixelSize(vp.pixelSize),
    numSamples(vp.numSamples),
    samplerPtr(vp.samplerPtr),
    maxDepth(vp.maxDepth)
{}

Viewplane::~Viewplane()
{}

