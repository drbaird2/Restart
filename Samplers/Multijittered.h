#ifndef MULTIJITTERED_H
#define MULTIJITTERED_H

#include "Sampler.h"

class MultiJittered :public Sampler{
    public:
	    MultiJittered();
	    MultiJittered(const int numSamples);
	    MultiJittered(const int numSamples, const int m);
	    MultiJittered(const MultiJittered& mjs);
	    ~MultiJittered();

	    MultiJittered& operator=(const MultiJittered& rhs);
	    shared_ptr<Sampler> clone() const override;

	    void generateSamples();
};

#endif