#ifndef MULTIJITTERED_H
#define MULTIJITTERED_H

#include "Sampler.h"

/*******************************************************************
 * Class - MultiJittered - Inherits from Sampler
 * 
 * A combination of N-Rooks and jittered sampling that shuffles
 * samples within divided cells to randomize in both dimensions
 * and withing the whole shape.
 *******************************************************************/

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