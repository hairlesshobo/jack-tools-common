#include <math.h>
#include <stdbool.h>

#include "biquad.h"
#include "filter.h"

#define PI (3.14159265358979323846)

R fosCoefStep(R x0, R b0, R b1, R a1, R *x1, R *y1) {
	R y0 = (b0 * x0) + (b1 * *x1) + (a1 * *y1);
	*x1 = x0;
	*y1 = y0;
	return y0;
}

R sosCoefStep(R x0, R b0, R b1, R b2, R a1, R a2, R *x1, R *x2, R *y1, R *y2) {
	return biquad_normalised_direct_form_1(x0, b0, b1, b2, -a1, -a2, x1, x2, y1, y2);
}

R iir2CoefStep(R x0, R b0, R a1, R a2, R *y1, R *y2) {
	R y0 = (b0 * x0) + (a1 * *y1) + (a2 * *y2);
	*y2 = *y1;
	*y1 = y0;
	return y0;
}

// Butterworth low pass or high pass Sos filter coefficients.
void bwLpfOrHpfCoef(bool isHpf, R sr, R freq, R rq, R *a0, R *a1, R *a2, R *b1, R *b2) {
	R f = freq * PI / sr;
	R c = isHpf ? tan(f) : 1 / tan(f);
	R c2 = c * c;
	R s2c = sqrt(2) * c;
	*a0 = 1 / (1 + s2c + c2);
	*a1 = isHpf ? -2 * *a0 : 2 * *a0;
	*a2 = *a0;
	*b1 = isHpf ? 2 * (c2 - 1) * *a0 : 2 * (1 - c2) * *a0;
	*b2 = (1 - s2c + c2) * *a0;
}

// Rlpf Iir2 coefficients, (a0, b1, b2).
void rlpfCoef(R radiansPerSample, R freq, R rq, R *a0, R *b1, R *b2) {
	R qr = 0.001 > rq ? 0.001 : rq;
	R pf = freq * radiansPerSample;
	R d = tan(pf * qr * 0.5);
	R c = (1 - d) / (1 + d);
	*b1 = (1 + c) * cos(pf);
	*a0 = (1 + c - *b1) * 0.25;
	*b2 = -c;
}

// Resonz Iir2 coefficients, (a0, b1, b2).
void resonzCoef(R radiansPerSample, R freq, R rq, R *a0, R *b1, R *b2) {
	R ff = freq * radiansPerSample;
	R b = ff * rq;
	R r = 1 - b * 0.5;
	R twoR = 2 * r;
	R r2 = r * r;
	R ct = (twoR * cos(ff)) / (1 + r2);
	*a0 = (1 - r2) * 0.5;
	*b1 = twoR * ct;
	*b2 = -r2;
}

R fosStep(R in, fos c, fosState s) { return fosCoefStep(in, c.a0, c.a1, c.b1, &s.in1, &s.out1); }
R sosStep(R in, sos c, sosState s) { return sosCoefStep(in, c.a0, c.a1, c.a2, c.b1, c.b2, &s.in1, &s.in2, &s.out1, &s.out2); }
R iir2Step(R in, iir2 c, iir2State s) { return iir2CoefStep(in, c.a0, c.b1, c.b2, &s.out1, &s.out2); }

sos bwLpfOrHpf(bool isHpf, R sr, R freq, R rq) { sos c; bwLpfOrHpfCoef(isHpf, sr, freq, rq, &c.a0, &c.a1, &c.a2, &c.b1, &c.b2); return c; }
iir2 rlpf(R radiansPerSample, R freq, R rq) { iir2 c; rlpfCoef(radiansPerSample, freq, rq, &c.a0, &c.b1, &c.b2); return c; }
iir2 resonz(R radiansPerSample, R freq, R rq) { iir2 c; resonzCoef(radiansPerSample, freq, rq, &c.a0, &c.b1, &c.b2); return c; }
