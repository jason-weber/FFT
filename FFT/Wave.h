#ifndef WAVE_H
#define WAVE_H

#include <vector>
#include <complex>
#include <string>
#include <algorithm>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <math.h>


class Wave{
public:
	typedef std::vector<std::complex<float>> VectorCf;

	Wave(VectorCf values, float sampleLengthInSeconds);

	VectorCf frequencyDomain;
	VectorCf timeDomain;
	float samplingInterval;
	float samplingRate;

	VectorCf calcFFT(VectorCf values);
	VectorCf calcInverseFFT(VectorCf values);
	
	float calculateSamplingRate(float sampleLength, unsigned int numberOfSamples);
	float calculateSamplingInterval(float sampleLength, unsigned int numberOfSamples);
	
	VectorCf conjugate(VectorCf values);
	VectorCf scale(VectorCf values);

	std::string toString();

};
#endif



