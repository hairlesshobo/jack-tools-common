#include <math.h>

#include "biquad.h"

R biquad_normalised_direct_form_1(R x0, R b0, R b1, R b2, R a1, R a2, R *x1, R *x2, R *y1, R *y2)
{
	R y0 = (b0 * x0) + (b1 * *x1) + (b2 * *x2) - (a1 * *y1) - (a2 * *y2);
	*x2 = *x1;
	*x1 = x0;
	*y2 = *y1;
	*y1 = y0;
	return y0;
}

R biquad_normalised_direct_form_2(R x0, R b0, R b1, R b2, R a1, R a2, R *w1, R *w2)
{
	R w0 = x0 - (a1 * *w1) - (a2 * *w2);
	R y0 = (b0 * w0) + (b1 * *w1) + (b2 * *w2);
	*w2 = *w1;
	*w1 = w0;
	return y0;
}

R biquad_transposed_normalised_direct_form_2(R x0, R b0, R b1, R b2, R a1, R a2, R *w1, R *w2)
{
	R y0 = (b0 * x0) + *w1;
	*w1 = (b1 * x0) - (a1 * y0) + *w2;
	*w2 = (b2 * x0) - (a2 * y0);
	return y0;
}
