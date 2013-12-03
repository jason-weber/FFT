#include "FFT.h"

std::vector<std::complex<float>> calcFFT(std::vector<std::complex<float>> values){
	//Resultant vector to return
	std::vector<std::complex<float>> fft(values.size());

	int size = values.size();
	
	//Base recursion case
	if(size <= 1){
		return values;
	}
	std::vector<std::complex<float>> even;
	std::vector<std::complex<float>> odd;

	//Fill even vector with all elements in values with even indices
	//Fill odd vector with all elements in values with odd indices
	for(int i = 0; i < size - 1; i += 2){
		even.push_back(values[i]);
		odd.push_back(values[i + 1]);
	}

	//Recursively call fft on even then odd indices
	even = calcFFT(even);
	odd = calcFFT(odd);

	//Combine even and odd
	for(int k = 0; k < size / 2; k++){
		//Compute the e^exp portion of the FFT
		float exp = (float)(-2 * k * M_PI / size);
		//Euler's Identity
		std::complex<float> complex(cos(exp), sin(exp));

		//Combine the 2 vectors into the resultant
		fft[k] = even[k] + (odd[k] * complex);
		fft[k + size / 2] = even[k] - (odd[k] * complex);
	}

	return fft;
	
}

std::vector<std::complex<float>> conjugate(std::vector<std::complex<float>> nums){
	std::vector<std::complex<float>> result;
	for(int i = 0; i < nums.size(); i++){
		result.push_back(std::conj(nums[i]));
	}
	return result;
}
std::vector<std::complex<float>> scale(std::vector<std::complex<float>> vals){
	int length = vals.size();
	for(int i = 0; i < length; i++){
		vals[i] /= length;
	}
	return vals;
}

std::vector<std::complex<float>> calcInverseFFT(std::vector<std::complex<float>> fft){
	fft = conjugate(fft);
	fft = calcFFT(fft);
	fft = conjugate(fft);
	fft = scale(fft);

	return fft;
}

std::string fftToString(std::vector<std::complex<float>> timeDomain, std::vector<std::complex<float>> frequencyDomain){
	std::ostringstream buff;
	buff << "\nSignal in the time domain: \n[\n";

	for(unsigned int i = 0; i < timeDomain.size() - 1; i++){
		buff << std::setprecision(2) << timeDomain.at(i).real();
		buff << " + ";
		buff << std::setprecision(2) << timeDomain.at(i).imag();
		buff << " * i, \n";
	}
	buff << std::setprecision(2) << timeDomain.at(timeDomain.size() - 1).real();
	buff << " + ";
	buff << std::setprecision(2) << timeDomain.at(timeDomain.size() - 1).imag();
	buff << " * i\n]\n\n";

	buff << "Signal in the frequency domain: \n[\n";

	for(unsigned int i = 0; i < frequencyDomain.size() - 1; i++){
		buff << std::setprecision(2) << frequencyDomain.at(i).real();
		buff << " + ";
		buff << std::setprecision(2) << frequencyDomain.at(i).imag();
		buff << " * i, \n";
	}
	buff << std::setprecision(2) << frequencyDomain.at(frequencyDomain.size() - 1).real();
	buff << " + ";
	buff << std::setprecision(2) << frequencyDomain.at(frequencyDomain.size() - 1).imag();
	buff << " * i\n]\n";

	return buff.str();
}