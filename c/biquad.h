#ifndef _COMMON_BIQUAD_H
#define _COMMON_BIQUAD_H

#define R double

R biquad_normalised_direct_form_1(R x0, R b0, R b1, R b2, R a1, R a2, R *x1, R *x2, R *y1, R *y2);
R biquad_normalised_direct_form_2(R x0, R b0, R b1, R b2, R a1, R a2, R *w1, R *w2);
R biquad_transposed_normalised_direct_form_2(R x0, R b0, R b1, R b2, R a1, R a2, R *w1, R *w2);

#endif
