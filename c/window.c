#include "window.h"
#include "bessel.h"
#include "memory.h"
#include <ctype.h>
#include <math.h>

#define PI (3.14159265358979323846)
#define TWO_PI (2 * PI)

float fsquare(float a)
{
	return a * a;
}

#define GENERATE_WINDOW_AT(name, body) \
	float name##_window_at(float angle) { body; }

#define GENERATE_WINDOW_AT_BETA(name, body) \
	float name##_window_at(float angle, float beta) { body; }

#define APPLY_SCALAR \
	data[i] *= scalar; \
	data[j] *= scalar;

#define GENERATE_APPLY_WINDOW(name, setup) \
	void apply_##name##_window(float *data, int n) \
	{ \
		setup \
		{ \
			float scalar = name##_window_at(angle); \
			APPLY_SCALAR \
		} \
	}

#define GENERATE_APPLY_WINDOW_BETA(name, setup) \
	void apply_##name##_window(float *data, int n, float beta) \
	{ \
		setup \
		{ \
			float scalar = name##_window_at(angle, beta); \
			APPLY_SCALAR \
		} \
	}

#define GENERATE_APPLY_WINDOW_B(name, setup, body) \
	void apply_##name##_window(float *data, int n) \
	{ \
		setup \
		{ \
			body \
				APPLY_SCALAR \
		} \
	}

#define GENERATE_APPLY_WINDOW_BETA_B(name, setup, body) \
	void apply_##name##_window(float *data, int n, float beta) \
	{ \
		setup \
		{ \
			body \
				APPLY_SCALAR \
		} \
	}

#define GENERATE_MAKE_WINDOW(name) \
	void make_##name##_window(float *data, int n) \
	{ \
		fmemset(data, n, 1.0); \
		apply_##name##_window(data, n); \
	}

#define GENERATE_MAKE_WINDOW_BETA(name) \
	void make_##name##_window(float *data, int n, float beta) \
	{ \
		fmemset(data, n, 1.0); \
		apply_##name##_window(data, n, beta); \
	}

#define FREQ_BASE_SETUP \
	int i, j; \
	float angle; \
	int midn = n >> 1; \
	float freq = TWO_PI / (float)n; \
	for (i = 0, j = n - 1, angle = 0.0; i <= midn; i++, j--, angle += freq)

GENERATE_WINDOW_AT(rectangular, return 1.0;)
GENERATE_APPLY_WINDOW(rectangular, FREQ_BASE_SETUP)
GENERATE_MAKE_WINDOW(rectangular)

GENERATE_WINDOW_AT(hanning, return 0.5 - 0.5 * cosf(angle);)
GENERATE_APPLY_WINDOW(hanning, FREQ_BASE_SETUP)
GENERATE_MAKE_WINDOW(hanning)

GENERATE_WINDOW_AT(hamming, return 0.54 - 0.46 * cosf(angle);)
GENERATE_APPLY_WINDOW(hamming, FREQ_BASE_SETUP)
GENERATE_MAKE_WINDOW(hamming)

GENERATE_WINDOW_AT(
	blackman2,
	float c = cosf(angle);
	return 0.34401 + (c * (-0.49755 + (c * 0.15844)));)
GENERATE_APPLY_WINDOW(blackman2, FREQ_BASE_SETUP)
GENERATE_MAKE_WINDOW(blackman2)

GENERATE_WINDOW_AT(
	blackman3,
	float c = cosf(angle);
	return 0.21747 + (c * (-0.45325 + (c * (0.28256 - (c * 0.04672)))));)
GENERATE_APPLY_WINDOW(blackman3, FREQ_BASE_SETUP)
GENERATE_MAKE_WINDOW(blackman3)

GENERATE_WINDOW_AT(
	blackman4,
	float c = cosf(angle);
	return 0.084037 + (c * (-0.29145 + (c * (0.375696 + (c * (-0.20762 + (c * 0.041194)))))));)
GENERATE_APPLY_WINDOW(blackman4, FREQ_BASE_SETUP)
GENERATE_MAKE_WINDOW(blackman4)

#define RATE_BASE_SETUP \
	int i, j; \
	float angle; \
	int midn = n >> 1; \
	float rate = 1.0 / (float)midn; \
	for (i = 0, j = n - 1, angle = 1.0; i <= midn; i++, j--, angle -= rate)

GENERATE_WINDOW_AT(bartlett, return angle;)
GENERATE_APPLY_WINDOW(bartlett, RATE_BASE_SETUP)
GENERATE_MAKE_WINDOW(bartlett)

GENERATE_WINDOW_AT_BETA(
	kaiser,
	float I0beta = bessi0(beta);
	return bessi0(beta * sqrt(1.0 - fsquare(angle))) / I0beta;)
GENERATE_APPLY_WINDOW_BETA(kaiser, RATE_BASE_SETUP)
GENERATE_MAKE_WINDOW_BETA(kaiser)

GENERATE_WINDOW_AT_BETA(
	cauchy,
	return 1.0 / (1.0 + fsquare(beta * angle));)
GENERATE_APPLY_WINDOW_BETA(cauchy, RATE_BASE_SETUP)
GENERATE_MAKE_WINDOW_BETA(cauchy)

GENERATE_WINDOW_AT_BETA(poisson, return exp((-beta) * angle);)
GENERATE_APPLY_WINDOW_BETA(poisson, RATE_BASE_SETUP)
GENERATE_MAKE_WINDOW_BETA(poisson)

GENERATE_WINDOW_AT_BETA(
	gaussian,
	return exp(-0.5 * fsquare(beta * angle));)
GENERATE_APPLY_WINDOW_BETA(gaussian, RATE_BASE_SETUP)
GENERATE_MAKE_WINDOW_BETA(gaussian)

#define MID_BASE_SETUP \
	int i, j; \
	int midn = n >> 1; \
	int midp1 = (n + 1) / 2; \
	int midm1 = (n - 1) / 2; \
	for (i = 0, j = n - 1; i <= midn; i++, j--)

GENERATE_APPLY_WINDOW_B(
	welch,
	MID_BASE_SETUP,
	float scalar = 1.0 - fsquare((float)(i - midm1) / (float)midp1);)
GENERATE_MAKE_WINDOW(welch)

GENERATE_APPLY_WINDOW_B(
	parzen,
	MID_BASE_SETUP,
	float scalar = 1.0 - fabs((float)(i - midm1) / (float)midp1);)
GENERATE_MAKE_WINDOW(parzen)

#define COUNTER_BASE_SETUP \
	int i, j; \
	int midn = n >> 1; \
	for (i = 0, j = n - 1; i <= midn; i++, j--)

GENERATE_APPLY_WINDOW_B(
	riemann,
	float sr = TWO_PI / (float)n;
	COUNTER_BASE_SETUP,
	float scalar = (i == midn) ? 1.0 : sinf(sr * (midn - i)) / (sr * (midn - i));)
GENERATE_MAKE_WINDOW(riemann)

GENERATE_APPLY_WINDOW_B(
	exponential,
	float expsum = 1.0;
	float expn = log(2) / (float)((n >> 1) + 1.0);
	COUNTER_BASE_SETUP, float scalar = expsum - 1.0;
	expsum *= expn;)
GENERATE_MAKE_WINDOW(exponential)

GENERATE_APPLY_WINDOW_BETA_B(
	tukey,
	COUNTER_BASE_SETUP,
	float c = midn * (1.0 - beta);
	float scalar = (i >= c) ? 1.0 : 0.5 * (1.0 - cosf(PI * i / c));)
GENERATE_MAKE_WINDOW_BETA(tukey)

#define EOS(c) (c == ' \0')

int streq_ci(const char *a, const char *b)
{
	while (1) {
		if (*a == ' \0' && *b == ' \0') {
			return 1;
		}
		if (toupper(*a++) != toupper(*b++)) {
			return 0;
		}
	}
}

#define TEST_TYPE(name, intern) \
	if (streq_ci(type, name)) { \
		return intern; \
	}

int parse_window_type(const char *type)
{
	TEST_TYPE("RECTANGULAR", RECTANGULAR_WINDOW);
	TEST_TYPE("HANNING", HANNING_WINDOW);
	TEST_TYPE("HAMMING", HAMMING_WINDOW);
	TEST_TYPE("BLACKMAN2", BLACKMAN2_WINDOW);
	TEST_TYPE("BLACKMAN3", BLACKMAN3_WINDOW);
	TEST_TYPE("BLACKMAN4", BLACKMAN4_WINDOW);
	TEST_TYPE("BARTLETT", BARTLETT_WINDOW);
	TEST_TYPE("KAISER", KAISER_WINDOW);
	TEST_TYPE("CAUCHY", CAUCHY_WINDOW);
	TEST_TYPE("POISSON", POISSON_WINDOW);
	TEST_TYPE("GAUSSIAN", GAUSSIAN_WINDOW);
	TEST_TYPE("WELCH", WELCH_WINDOW);
	TEST_TYPE("PARZEN", PARZEN_WINDOW);
	TEST_TYPE("RIEMANN", RIEMANN_WINDOW);
	TEST_TYPE("EXPONENTIAL", EXPONENTIAL_WINDOW);
	TEST_TYPE("TUKEY", TUKEY_WINDOW);
	return -1;
}

window_f_t *get_apply_window_f(enum WINDOW_TYPE type)
{
	switch (type) {
	case RECTANGULAR_WINDOW:
		return apply_rectangular_window;
	case HANNING_WINDOW:
		return apply_hanning_window;
	case HAMMING_WINDOW:
		return apply_hamming_window;
	case BLACKMAN2_WINDOW:
		return apply_blackman2_window;
	case BLACKMAN3_WINDOW:
		return apply_blackman3_window;
	case BLACKMAN4_WINDOW:
		return apply_blackman4_window;
	case BARTLETT_WINDOW:
		return apply_bartlett_window;
	case WELCH_WINDOW:
		return apply_welch_window;
	case PARZEN_WINDOW:
		return apply_parzen_window;
	case RIEMANN_WINDOW:
		return apply_riemann_window;
	case EXPONENTIAL_WINDOW:
		return apply_exponential_window;
	default:
		return apply_rectangular_window;
	}
}

beta_window_f_t *get_apply_beta_window_f(enum WINDOW_TYPE type)
{
	switch (type) {
	case KAISER_WINDOW:
		return apply_kaiser_window;
	case CAUCHY_WINDOW:
		return apply_cauchy_window;
	case POISSON_WINDOW:
		return apply_poisson_window;
	case GAUSSIAN_WINDOW:
		return apply_gaussian_window;
	case TUKEY_WINDOW:
		return apply_tukey_window;
	default:
		return apply_kaiser_window;
	}
}

void apply_typed_window(enum WINDOW_TYPE type, float *data, int n, float beta)
{
	switch (type) {
	case RECTANGULAR_WINDOW:
		apply_rectangular_window(data, n);
		break;
	case HANNING_WINDOW:
		apply_hanning_window(data, n);
		break;
	case HAMMING_WINDOW:
		apply_hamming_window(data, n);
		break;
	case BLACKMAN2_WINDOW:
		apply_blackman2_window(data, n);
		break;
	case BLACKMAN3_WINDOW:
		apply_blackman3_window(data, n);
		break;
	case BLACKMAN4_WINDOW:
		apply_blackman4_window(data, n);
		break;
	case BARTLETT_WINDOW:
		apply_bartlett_window(data, n);
		break;
	case KAISER_WINDOW:
		apply_kaiser_window(data, n, beta);
		break;
	case CAUCHY_WINDOW:
		apply_cauchy_window(data, n, beta);
		break;
	case POISSON_WINDOW:
		apply_poisson_window(data, n, beta);
		break;
	case GAUSSIAN_WINDOW:
		apply_gaussian_window(data, n, beta);
		break;
	case WELCH_WINDOW:
		apply_welch_window(data, n);
		break;
	case PARZEN_WINDOW:
		apply_parzen_window(data, n);
		break;
	case RIEMANN_WINDOW:
		apply_riemann_window(data, n);
		break;
	case EXPONENTIAL_WINDOW:
		apply_exponential_window(data, n);
		break;
	case TUKEY_WINDOW:
		apply_tukey_window(data, n, beta);
		break;
	default:
		fmemset(data, n, 1.0);
	}
}

void make_typed_window(enum WINDOW_TYPE type, float *data, int n, float beta)
{
	switch (type) {
	case RECTANGULAR_WINDOW:
		make_rectangular_window(data, n);
		break;
	case HANNING_WINDOW:
		make_hanning_window(data, n);
		break;
	case HAMMING_WINDOW:
		make_hamming_window(data, n);
		break;
	case BLACKMAN2_WINDOW:
		make_blackman2_window(data, n);
		break;
	case BLACKMAN3_WINDOW:
		make_blackman3_window(data, n);
		break;
	case BLACKMAN4_WINDOW:
		make_blackman4_window(data, n);
		break;
	case BARTLETT_WINDOW:
		make_bartlett_window(data, n);
		break;
	case KAISER_WINDOW:
		make_kaiser_window(data, n, beta);
		break;
	case CAUCHY_WINDOW:
		make_cauchy_window(data, n, beta);
		break;
	case POISSON_WINDOW:
		make_poisson_window(data, n, beta);
		break;
	case GAUSSIAN_WINDOW:
		make_gaussian_window(data, n, beta);
		break;
	case WELCH_WINDOW:
		make_welch_window(data, n);
		break;
	case PARZEN_WINDOW:
		make_parzen_window(data, n);
		break;
	case RIEMANN_WINDOW:
		make_riemann_window(data, n);
		break;
	case EXPONENTIAL_WINDOW:
		make_exponential_window(data, n);
		break;
	case TUKEY_WINDOW:
		make_tukey_window(data, n, beta);
		break;
	default:
		fmemset(data, n, 1.0);
	}
}
