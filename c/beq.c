/* Beq filter coefficient calculations, results are (a0, a1, a2, b1, b2). */

#include <math.h>

#include "beq.h"

#define PI (3.14159265358979323846)

// Calculate coefficients for bi-quad low pass filter.
void beqLowPassCoef(R sr, R freq, R rq, R *a0, R *a1, R *a2, R *b1, R *b2) {
	R w0 = PI * 2 * freq * (1 / sr);
	R cos_w0 = cos(w0);
	R i = 1 - cos_w0;
	R alpha = sin(w0) * 0.5 * rq;
	R b0rz = 1 / (1 + alpha);
	*a0 = i * 0.5 * b0rz;
	*a1 = i * b0rz;
	*a2 = *a0;
	*b1 = cos_w0 * 2 * b0rz;
	*b2 = (1 - alpha) * -b0rz;
}

// Calculate coefficients for bi-quad high pass filter.
void beqHiPassCoef(R sr, R freq, R rq, R *a0, R *a1, R *a2, R *b1, R *b2) {
	R w0 = PI * 2 * freq * (1 / sr);
	R cos_w0 = cos(w0);
	R i = 1 + cos_w0;
	R alpha = sin(w0) * 0.5 * rq;
	R b0rz = 1 / (1 + alpha);
	*a0 = i * 0.5 * b0rz;
	*a1 = -i * b0rz;
	*a2 = *a0;
	*b1 = cos_w0 * 2 * b0rz;
	*b2 = (1 - alpha) * -b0rz;
}

// Calculate coefficients for bi-quad all pass filter.
void beqAllPassCoef(R sr, R freq, R rq, R *a0, R *a1, R *a2, R *b1, R *b2) {
	R w0 = PI * 2 * freq * (1 / sr);
	R alpha = sin(w0) * 0.5 * rq;
	R b0rz = 1 / (1 + alpha);
	*a0 = (1 - alpha) * b0rz;
	*a2 = 1;
	*b1 = 2 * cos(w0) * b0rz;
	*a1 = -*b1;
	*b2 = -*a0;
}

// Calculate coefficients for bi-quad band pass filter.
void beqBandPassCoef(R sr, R freq, R bw, R *a0, R *a1, R *a2, R *b1, R *b2) {
	R w0 = PI * 2 * freq * (1 / sr);
	R sin_w0 = sin(w0);
	R alpha = sin_w0 * sinh(0.34657359027997 * bw * w0 / sin_w0);
	R b0rz = 1 / (1 + alpha);
	*a0 = alpha * b0rz;
	*a1 = 0;
	*a2 = -*a0;
	*b1 = cos(w0) * 2 * b0rz;
	*b2 = (1 - alpha) * -b0rz;
}

// Calculate coefficients for bi-quad stop band filter.
void beqBandStopCoef(R sr, R freq, R bw, R *a0, R *a1, R *a2, R *b1, R *b2) {
	R w0 = PI * 2 * freq * (1 / sr);
	R sin_w0 = sin(w0);
	R alpha = sin_w0 * sinh(0.34657359027997 * bw * w0 / sin_w0);
	R b0rz = 1 / (1 + alpha);
	*a0 = b0rz;
	*a2 = b0rz;
	*b1 = 2 * cos(w0) * b0rz;
	*a1 = -*b1;
	*b2 = (1 - alpha) * -b0rz;
}

// Calculate coefficients for bi-quad peaking EQ filter.
void beqPeakEqCoef(R sr, R freq, R rq, R db, R *a0, R *a1, R *a2, R *b1, R *b2) {
	R a = pow(10, db / 40);
	R w0 = PI * 2 * freq * (1 / sr);
	R alpha = sin(w0) * 0.5 * rq;
	R b0rz = 1 / (1 + (alpha / a));
	*a0 = (1 + (alpha * a)) * b0rz;
	*a2 = (1 - (alpha * a)) * b0rz;
	*b1 = 2 * cos(w0) * b0rz;
	*a1 = -*b1;
	*b2 = (1 - (alpha / a)) * -b0rz;
}

// Calculate coefficients for bi-quad low shelf filter.
void beqLowShelfCoef(R sr, R freq, R rs, R db, R *a0, R *a1, R *a2, R *b1, R *b2) {
	R a = pow(10, db / 40);
	R w0 = PI * 2 * freq * (1 / sr);
	R cos_w0 = cos(w0);
	R sin_w0 = sin(w0);
	R alpha = sin_w0 * 0.5 * sqrt((a + (1 / a)) * (rs - 1) + 2);
	R i = (a + 1) * cos_w0;
	R j = (a - 1) * cos_w0;
	R k = 2 * sqrt(a) * alpha;
	R b0rz = 1 / ((a + 1) + j + k);
	*a0 = a * ((a + 1) - j + k) * b0rz;
	*a1 = 2 * a * ((a - 1) - i) * b0rz;
	*a2 = a * ((a + 1) - j - k) * b0rz;
	*b1 = 2 * ((a - 1) + i) * b0rz;
	*b2 = ((a + 1) + j - k) * -b0rz;
}

// Calculate coefficients for bi-quad high shelf filter.
void beqHiShelfCoef(R sr, R freq, R rs, R db, R *a0, R *a1, R *a2, R *b1, R *b2) {
	R a = pow(10, db / 40);
	R w0 = PI * 2 * freq * (1 / sr);
	R cos_w0 = cos(w0);
	R sin_w0 = sin(w0);
	R alpha = sin_w0 * 0.5 * sqrt((a + (1 / a)) * (rs - 1) + 2);
	R i = (a + 1) * cos_w0;
	R j = (a - 1) * cos_w0;
	R k = 2 * sqrt(a) * alpha;
	R b0rz = 1 / ((a + 1) - j + k);
	*a0 = a * ((a + 1) + j + k) * b0rz;
	*a1 = -2 * a * ((a - 1) + i) * b0rz;
	*a2 = a * ((a + 1) + j - k) * b0rz;
	*b1 = -2 * ((a - 1) - i) * b0rz;
	*b2 = ((a + 1) - j - k) * -b0rz;
}

sos beqLowPass(R sr, R freq, R rq) { sos c; beqLowPassCoef(sr, freq, rq, &c.a0, &c.a1, &c.a2, &c.b1, &c.b2); return c; }
sos beqHiPass(R sr, R freq, R rq) { sos c; beqHiPassCoef(sr, freq, rq, &c.a0, &c.a1, &c.a2, &c.b1, &c.b2); return c; }
sos beqAllPass(R sr, R freq, R rq) { sos c; beqAllPassCoef(sr, freq, rq, &c.a0, &c.a1, &c.a2, &c.b1, &c.b2); return c; }
sos beqBandPass(R sr, R freq, R bw) { sos c; beqBandPassCoef(sr, freq, bw, &c.a0, &c.a1, &c.a2, &c.b1, &c.b2); return c; }
sos beqBandStop(R sr, R freq, R bw) { sos c; beqBandStopCoef(sr, freq, bw, &c.a0, &c.a1, &c.a2, &c.b1, &c.b2); return c; }
sos beqPeakEq(R sr, R freq, R rq, R db) { sos c; beqPeakEqCoef(sr, freq, rq, db, &c.a0, &c.a1, &c.a2, &c.b1, &c.b2); return c; }
sos beqLowShelf(R sr, R freq, R rs, R db) { sos c; beqLowShelfCoef(sr, freq, rs, db, &c.a0, &c.a1, &c.a2, &c.b1, &c.b2); return c; }
sos beqHiShelf(R sr, R freq, R rs, R db) { sos c; beqHiShelfCoef(sr, freq, rs, db, &c.a0, &c.a1, &c.a2, &c.b1, &c.b2); return c; }
