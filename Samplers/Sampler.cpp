#include "Sampler.h"
#include "../Utilities/Constants.h"
#include "../Utilities/Vec3.h"
#include <random>
#include <numeric>
#include <algorithm>
#include <cmath>


/*******************************************************************
 * Constructors
 * 
 *******************************************************************/
Sampler::Sampler():
    numSamples(1),
	numSets(83),
	count(0),
	jump(0)
{
	samples.reserve(numSamples * numSets);
	setupShuffledIndices();
}

Sampler::Sampler(const int ns):
	numSamples(ns),
	numSets(83),
	count(0),
	jump(0)
{
	samples.reserve(numSamples * numSets);
	setupShuffledIndices();
}

Sampler::Sampler(const int ns, const int nSets):
	numSamples(ns),
	numSets(nSets),
	count(0),
	jump(0)
{
	samples.reserve(numSamples * numSets);
	setupShuffledIndices();
}

Sampler::Sampler(const Sampler& s):
	numSamples(s.numSamples),
	numSets(s.numSets),
	samples(s.samples),
	shuffledIndices(s.shuffledIndices),
	count(s.count),
	jump(s.jump)
{

}

/*******************************************************************
 * Assignment opperator
 * 
 *******************************************************************/

Sampler& Sampler::operator=(const Sampler& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	numSamples = rhs.numSamples;
	numSets = rhs.numSets;
	samples = rhs.samples; 
	shuffledIndices = rhs.shuffledIndices;
	count = rhs.count;
	jump = rhs.jump;

	return *this;
}

Sampler::~Sampler()
{}

/*******************************************************************
 * setupShuffledIndices - Used to create a series of randomized 
 * 							sample sets
 * 
 *******************************************************************/

void Sampler::setupShuffledIndices(){
	//reserve vector
	shuffledIndices.reserve(numSamples * numSets);
	
	//make indices
	vector<int> indices(numSamples);
	iota(indices.begin(), indices.end(), 0);

	//make random device
	std::random_device seed;
	std::mt19937 engine(seed());

	for (int p = 0; p < numSets; p++)
	{
		std::shuffle(indices.begin(), indices.end(),engine);

		for (int j = 0; j < numSamples; j++)
		{
			shuffledIndices.push_back(indices[j]);
		}
	}
}

void Sampler::setNumSets(const int np){
	numSets = np;
}

int Sampler::getNumSamples(){
	return numSamples;
}

/*******************************************************************
 * Sample unit components to generate the actual samples
 * 
 *******************************************************************/
Point2 Sampler::sampleUnitSquare(){
	//random
	random_device rd;
	mt19937 mt(rd());

	if (count % numSamples == 0)
	{
		jump = (mt() % numSets) * numSamples;
	}

	return samples[jump + shuffledIndices[jump + count++ % numSamples]];

}


Point2 Sampler::sampleUnitDisk(){
	//random
	std::random_device rd;
	std::mt19937 mt(rd());

	if (count % numSamples == 0)
	{
		jump = (mt() % numSets) * numSamples;
	}

	return diskSamples[jump + shuffledIndices[jump + count++ % numSamples]];

}


Point3 Sampler::sampleHemisphere(){
	//random
	random_device rd;
	mt19937 mt(rd());

	if (count % numSamples == 0)
	{
		jump = (mt() % numSets) * numSamples;
	}

	return hemisphereSamples[jump + shuffledIndices[jump + count++ % numSamples]];

}

/*******************************************************************
 * Shufflers - shuffle the various x and y coordinates of the 
 * 				generated samples
 * 
 *******************************************************************/

void Sampler::shuffleXCoordinates(){
	random_device rd;
	mt19937 mt(rd());

	for (int p = 0; p < numSets; p++)
	{
		for (int i = 0; i < numSamples - 1; i++)
		{
			int target = mt() % numSamples + p * numSamples;
			float temp = samples[i + p * numSamples + 1].xPoint;
			samples[i + p * numSamples + 1].xPoint = samples[target].xPoint;
			samples[target].xPoint = temp;
		}
	}
}

void Sampler::shuffleYCoordinates(){
	random_device rd;
	mt19937 mt(rd());

	for (int p = 0; p < numSets; p++)
	{
		for (int i = 0; i < numSamples - 1; i++)
		{
			int target = mt() % numSamples + p * numSamples;
			float temp = samples[i + p * numSamples + 1].yPoint;
			samples[i + p * numSamples + 1].yPoint = samples[target].yPoint;
			samples[target].yPoint = temp;
		}
	}
}

/*******************************************************************
 * Map the taken samples from a unit square to a unit disk
 * 
 *******************************************************************/
void Sampler::mapSamplesToUnitDisk(){
	int size = samples.size();
	float r, phi;
	Point2 sp;
	
	diskSamples.resize(size);

	for (int j = 0; j < size; j++)
	{
		sp.xPoint = 2.0 * samples[j].xPoint - 1.0;
		sp.yPoint = 2.0 * samples[j].yPoint - 1.0;

		if (sp.xPoint > -sp.yPoint)
		{
			if (sp.xPoint > sp.yPoint)
			{
				//section 1
				r = sp.xPoint;
				phi = sp.yPoint / sp.xPoint;
			}
			else
			{
				//section 2
				r = sp.yPoint;
				phi = 2 - sp.xPoint / sp.yPoint;
			}
		}
		else
		{
			if (sp.xPoint < sp.yPoint)
			{
				//section 3
				r = -sp.xPoint;
				phi = 4 + sp.yPoint / sp.xPoint;
			}
			else
			{
				//section 4
				r = -sp.yPoint;

				if (sp.yPoint != 0.0)
				{
					phi = 6 - sp.xPoint / sp.yPoint;
				}
				else
				{
					phi = 0.0;
				}
			}
		}

		phi *= PI / 4.0;

		diskSamples[j].xPoint = r * cos(phi);
		diskSamples[j].yPoint = r * sin(phi);
	}

	samples.erase(samples.begin(), samples.end());
}

/*******************************************************************
 * Map the samples from a unit square to a hemisphere
 * 
 *******************************************************************/
void Sampler::mapSamplesToHemisphere(const float e)
{
	int size = samples.size();
	hemisphereSamples.reserve(numSamples * numSets);

	for (int j = 0; j < size; j++)
	{
		float cosPhi = cos(2.0 * PI * samples[j].xPoint);
		float sinPhi = sin(2.0 * PI * samples[j].xPoint);
		float cosTheta = pow((1.0 - samples[j].yPoint), 1.0 / (e + 1.0));
		float sinTheta = sqrt(1.0 - cosTheta * cosTheta);
		float pu = sinTheta * cosPhi;
		float pv = sinTheta * sinPhi;
		float pw = cosTheta;

		hemisphereSamples.emplace_back(Point3(pu, pv, pw));
	}
}