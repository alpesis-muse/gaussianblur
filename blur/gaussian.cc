#include <algorithm>
#include <cmath>
#include "gaussian.hh"
#include "utils/utils.hh"
#include "config.hh"

using namespace std;


GaussCache::GaussCache(float sigma) {
	// TODO decide window size ?
	/*
	 *const int kw = round(GAUSS_WINDOW_FACTOR * sigma) + 1;
	 */
	kw = ceil(0.3 * (sigma / 2 - 1) + 0.8) * GAUSS_WINDOW_FACTOR;
	//cout << kw << " " << sigma << endl;
	if (kw % 2 == 0) kw ++;
	kernel_buf.reset(new float[kw]);
	const int center = kw / 2;
	kernel = kernel_buf.get() + center;

	kernel[0] = 1;

	float exp_coeff = -1.0 / (sigma * sigma * 2),
				 wsum = 1;
	for (int i = 1; i <= center; i ++)
		wsum += (kernel[i] = exp(i * i * exp_coeff)) * 2;

	float fac = 1.0 / wsum;
	kernel[0] = fac;
	for (int i = 1; i <= center; i ++)
		kernel[-i] = (kernel[i] *= fac);
}


GaussCacheFull::GaussCacheFull(float sigma) {
	kw = ceil(0.3 * (sigma / 2 - 1) + 0.8) * GAUSS_WINDOW_FACTOR;
	if (kw % 2 == 0) kw ++;
	kernel_buf.reset(new float[kw*kw]);

	const int center = kw / 2;
	kernel = kernel_buf.get();
	
	// initialize
	double sum = 0.;
	double r;
	double exp_coeff = 2 * sigma * sigma;

	// generating the kernel
	for (int i = -center; i <= center; ++i) {
		for (int j = -center; j <= center; ++j) {
			r = sqrt(i * i + j * j);
			kernel[(i+center)*kw + (j+center)] = exp(-r*r/exp_coeff) / (M_PI*exp_coeff);
			sum += kernel[(i+center)*kw + (j+center)];
		}
	}

	// normalizing the kernel
	for (int i = -center; i <= center; ++i) {
		for (int j = -center; j <= center; ++j) {
			kernel[(i+center)*kw + (j+center)] /= sum;
		}
	}
}
