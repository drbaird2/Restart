#include "Viewplane.h"


Viewplane::Viewplane():
    hres(400), 
	vres(400),
	ps(1.0),
    numSamples(1)
{}

Viewplane::Viewplane(const Viewplane& vp):
    hres(vp.hres), 
	vres(vp.vres),
	ps(vp.ps),
    numSamples(vp.numSamples)
{}
Viewplane::~Viewplane()
{}

