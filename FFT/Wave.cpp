#include "Wave.h"

Wave::Wave(VectorCf* values, float sampleLengthInSeconds){
	this->timeDomain = values;
	this->frequencyDomain = this->calcFFT(values);
	this->sampleLength = sampleLengthInSeconds;
	this->samplingInterval = this->calculateSamplingInterval(sampleLengthInSeconds, values->size());
	this->samplingRate = 1 / this->samplingInterval;
	this->magnitudes = new std::vector<float>(values->size());
	for(unsigned int i = 0; i < magnitudes->size(); i++){
		magnitudes->at(i) = this->getMagnitude(frequencyDomain->at(i));
	}
}

float Wave::getMagnitude(std::complex<float> num){
	//Return the magnitude of the given complex number
	return std::sqrtf(num.real() * num.real() + num.imag() * num.imag());
}

float Wave::calculateSamplingInterval(float sampleLength, unsigned int numberOfSamples){
	return sampleLength / numberOfSamples;
}

float Wave::calculateSamplingRate(float sampleLength, unsigned int numberOfSamples){
	return numberOfSamples / sampleLength;
}

//Calculates the FFT of a signal. Values.size() must be a power of 2
Wave::VectorCf* Wave::calcFFT(Wave::VectorCf* values){
	//Create resulting vector
	int size = values->size();
	VectorCf* fft = new VectorCf(size);

	//Base case
	if(size <= 1){
		return values;
	}

	//Split vector into 2 vectors of the even indices and odd indices
	VectorCf* even = new VectorCf();;
	VectorCf* odd = new VectorCf();
	for(int i = 0; i < size - 1; i += 2){
		even->push_back(values->at(i));
		odd->push_back(values->at(i + 1));
	}

	//FFT on the 2 new vectors
	even = calcFFT(even);
	odd = calcFFT(odd);

	//Calculate
	for(int k = 0; k < size / 2; k++){	
		//Euler's Identity
		float exp = (float)(-2 * k * PI / size);
		std::complex<float> complex(cos(exp), sin(exp));
		
		//Butterfly operation
		fft->at(k) = even->at(k) + (odd->at(k) * complex);
		fft->at(k + size / 2) = even->at(k) - (odd->at(k) * complex);
	}
	
	return fft;
}

//Conjugates the complex values of the signal
Wave::VectorCf* Wave::conjugate(Wave::VectorCf* values){
	VectorCf* result = new VectorCf();
	for(unsigned int i = 0; i < values->size(); i++){
		result->push_back(std::conj(values->at(i)));
	}
	return result;
}

//Scale the values down by the number of values
Wave::VectorCf* Wave::scale(Wave::VectorCf* values){
	int length = values->size();
	for(int i = 0; i < length; i++){
		values->at(i) /= (float)length;
	}
	return values;
}

//Converts an FFT to the time domain
Wave::VectorCf* Wave::calcInverseFFT(VectorCf* fft){
	VectorCf* ifft = new VectorCf(*fft);
	ifft = conjugate(ifft);
	ifft = calcFFT(ifft);
	ifft = conjugate(ifft);
	ifft = scale(ifft);
	
	return ifft;
}

std::string Wave::toString(){
	std::ostringstream buff;
	
	//Convert time graph to a string
	buff << "Signal in the time domain: \n[\n";
	for(unsigned int i = 0; i < timeDomain->size() - 1; i++){
		buff << std::setprecision(2) << timeDomain->at(i).real();
		buff << " + ";
		buff << std::setprecision(2) << timeDomain->at(i).imag();
		buff << " * i, \n";
	}
	buff << std::setprecision(2) << timeDomain->at(timeDomain->size() - 1).real();
	buff << " + ";
	buff << std::setprecision(2) << timeDomain->at(timeDomain->size() - 1).imag();
	buff << " * i\n]\n\n";

	//Convert frequency graph to a string
	buff << "Signal in the frequency domain: \n[\n";
	for(unsigned int i = 0; i < frequencyDomain->size() - 1; i++){
		buff << std::setprecision(2) << frequencyDomain->at(i).real();
		buff << " + ";
		buff << std::setprecision(2) << frequencyDomain->at(i).imag();
		buff << " * i, \n";
	}
	buff << std::setprecision(2) << frequencyDomain->at(frequencyDomain->size() - 1).real();
	buff << " + ";
	buff << std::setprecision(2) << frequencyDomain->at(frequencyDomain->size() - 1).imag();
	buff << " * i\n]\n";

	//Convert magnitudes to string
	buff << "\nFrequency magnitudes: \n[\n";
	for(unsigned int i = 0; i < magnitudes->size() - 1; i++){
		buff << magnitudes->at(i) << " at " << i * this->samplingRate / timeDomain->size() << " Hz,\n";
	}
	buff << magnitudes->at(magnitudes->size() - 1) << " at " << (magnitudes->size() - 1) * this->samplingRate / timeDomain->size() << " Hz\n]\n";

	return buff.str();
}