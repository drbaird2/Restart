#ifndef SAMPLER_H
#define SAMPLER_H

#include "../Utilities/Point2.h"
#include "../Utilities/Vec3.h"
#include <vector>
#include <memory>

using namespace std;

class Sampler{
    public:
        int numSamples;
	    int numSets;
	    vector<Point2> samples;
	    vector<Point2> diskSamples;
	    vector<Point3> hemisphereSamples;
	    vector<int> shuffledIndices;
	    unsigned long count;
	    int jump;

	    Sampler();
	    Sampler(const int num);
	    Sampler(const int num, const int numSets);
	    Sampler(const Sampler& s);
	    virtual ~Sampler();

	    Sampler& operator=(const Sampler& rhs);
	    virtual shared_ptr<Sampler>clone() const { return move(make_shared<Sampler>(*this)); };

	    virtual void generateSamples(){};
	    void setupShuffledIndices();
	    void setNumSets(const int np);
	    int getNumSamples();
	    void shuffleXCoordinates();
	    void shuffleYCoordinates();

	//convert disk from square
	    void mapSamplesToUnitDisk();
	//convert hemisphere from spuare
	    void mapSamplesToHemisphere(const float p);

	    Point2 sampleUnitSquare();
	    Point2 sampleUnitDisk();
	    Point3 sampleHemisphere();	
};

#endif