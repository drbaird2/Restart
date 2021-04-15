#include "MultiJittered.h"
#include <random>
#include <cmath>

MultiJittered::MultiJittered(): 
    Sampler()
{

}

MultiJittered::MultiJittered(const int numSamples):
    Sampler(numSamples)
{
	generateSamples();
}

MultiJittered::MultiJittered(const int numSamples, const int m):
    Sampler(numSamples, m)
{
	generateSamples();
}

MultiJittered::MultiJittered(const MultiJittered& mjs):
    Sampler(mjs)
{}

MultiJittered::~MultiJittered()
{}

MultiJittered& MultiJittered::operator=(const MultiJittered& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	Sampler::operator=(rhs);

	return *this;
}

shared_ptr<Sampler> MultiJittered::clone() const
{
	return move(make_shared<Sampler>(*this));
}

void MultiJittered::generateSamples(){
	int n = sqrt(numSamples);
	float subCellWidth = 1.0 / numSamples;

	//fill ths sample array
	Point2 fillPoint;
	for (int j = 0; j < numSamples * numSets; j++)
	{
		samples.push_back(fillPoint);
	}

	//initialize
	random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> floatRand(0.0f, subCellWidth);

	for (int p = 0; p < numSets; p++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				samples[i * n + j + p * numSamples].xPoint = (i * n + j) * subCellWidth + floatRand(mt);
				samples[i * n + j + p * numSamples].yPoint = (j * n + i) * subCellWidth + floatRand(mt);
			}
		}
	}

	// shuffle x coordinates
	for (int p = 0; p < numSets; p++) 
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				std::uniform_int_distribution<int> intRand(j, n - 1);
				int k = intRand(mt);
				float t = samples[i * n + j + p * numSamples].xPoint;
				samples[i * n + j + p * numSamples].xPoint = samples[i * n + k + p * numSamples].xPoint;
				samples[i * n + k + p * numSamples].xPoint = t;
			}
		}
	}

	// shuffle y coordinates
	for (int p = 0; p < numSets; p++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				std::uniform_int_distribution<int> intRand(j, n - 1);
				int k = intRand(mt);
				float t = samples[j * n + i + p * numSamples].yPoint;
				samples[j * n + i + p * numSamples].yPoint = samples[j * n + k + p * numSamples].yPoint;
				samples[j * n + k + p * numSamples].yPoint = t;
			}
		}
	}
}