#ifndef _COMMON_FILTER_H
#define _COMMON_FILTER_H

#include <stdbool.h>

#define R double

R fosCoefStep(R in, R a0, R a1, R b1, R *in1, R *out1);
R sosCoefStep(R in, R a0, R a1, R a2, R b1, R b2, R *in1, R *in2, R *out1, R *out2);
R iir2CoefStep(R in, R a0, R b1, R b2, R *out1, R *out2);

void bwLpfOrHpfCoef(bool isHpf, R sr, R freq, R rq, R *a0, R *a1, R *a2, R *b1, R *b2);
void rlpfCoef(R radiansPerSample, R freq, R rq, R *a0, R *b1, R *b2);
void resonzCoef(R radiansPerSample, R freq, R rq, R *a0, R *b1, R *b2);

typedef struct {R a0, a1, b1;} fos;
typedef struct {R a0, a1, a2, b1, b2;} sos;
typedef struct {R a0, b1, b2;} iir2;

sos bwLpfOrHpf(bool isHpf, R sr, R freq, R rq);
iir2 rlpf(R radiansPerSample, R freq, R rq);
iir2 resonz(R radiansPerSample, R freq, R rq);

typedef struct {R in1, out1;} fosState;
typedef struct {R in1, in2, out1, out2;} sosState;
typedef struct {R out1, out2;} iir2State;

R fosStep(R in, fos c, fosState s);
R sosStep(R in, sos c, sosState s);
R iir2Step(R in, iir2 c, iir2State s);

#endif
