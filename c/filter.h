#ifndef _COMMON_FILTER_H
#define _COMMON_FILTER_H

#define R double

void bwLpfOrHpfCoef(bool isHpf, R sr, R freq, R rq, R *a0, R *a1, R *a2, R *b1, R *b2);
void rlpfCoef(R radiansPerSample, R freq, R rq, R *a0, R *b1, R *b2);
void resonzCoef(R radiansPerSample, R freq, R rq, R *a0, R *b1, R *b2);

typedef struct {R a0, a1, a2, b1, b2;} sos;
typedef struct {R a0, b1, b2;} iir2;

sos bwLpfOrHpf(bool isHpf, R sr, R freq, R rq);
iir2 rlpf(R radiansPerSample, R freq, R rq);
iir2 resonz(R radiansPerSample, R freq, R rq);

#endif
