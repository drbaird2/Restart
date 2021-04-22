#ifndef VIEWPLANE_H
#define VIEWPLANE_H

#include "../Samplers/Sampler.h"
#include "../Samplers/Multijittered.h"


class Viewplane{
    public:
        int         		hres;
        int         		vres;
        double      		pixelSize;
        int         		numSamples;
		int					maxDepth;
        shared_ptr<Sampler> samplerPtr;

    Viewplane();
    Viewplane(const Viewplane& vp);
    ~Viewplane();

    Viewplane& operator=(const Viewplane& rhs);

    void setHres(const int hres);
    void setVres(const int vres);
    void setPixelSize(const float size);
    void setSamples(const int n);   
    void setSampler(shared_ptr<Sampler> sp); 
	void setMaxDepth(const int depth);    

};

inline Viewplane& Viewplane::operator=(const Viewplane& rhs){
    if (this == &rhs)
		return (*this);
		
	hres 				= rhs.hres;
	vres 				= rhs.vres;
	pixelSize			= rhs.pixelSize;
	
	return (*this);
}


inline void Viewplane::setHres(const int h_res) { 
    hres = h_res;
}

inline void Viewplane::setVres(const int v_res) {
	vres = v_res;
}

inline void Viewplane::setPixelSize(const float size) {
	pixelSize = size;
}

inline void Viewplane::setSamples(const int n) {
	numSamples = n;

	if (samplerPtr){
		samplerPtr.reset();
		samplerPtr = nullptr;
	}

	if (numSamples > 1){
		samplerPtr = move(make_shared<MultiJittered>(numSamples));
	}
}

inline void Viewplane::setSampler(shared_ptr<Sampler> sp){
	if (samplerPtr){
		samplerPtr.reset();
	}

	numSamples = sp->getNumSamples();
	samplerPtr = sp;
}

inline void Viewplane::setMaxDepth(const int depth)
{
	maxDepth = depth;
}

#endif