#include <vector>
#include <complex>
#include <string>
#include <algorithm>
#include <iomanip>
#define _USE_MATH_DEFINES
#include <math.h>

std::vector<std::complex<float>> calcFFT(std::vector<std::complex<float>> values);
std::vector<std::complex<float>> calcInverseFFT(std::vector<std::complex<float>> values);
std::string fftToString(std::vector<std::complex<float>> timeDomain, std::vector<std::complex<float>> frequencyDomain);

