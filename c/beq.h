#ifndef _COMMON_BEQ_H
#define _COMMON_BEQ_H

#include "filter.h"

void beqLowPassCoef(R sr, R freq, R rq, R *a0, R *a1, R *a2, R *b1, R *b2);
void beqHiPassCoef(R sr, R freq, R rq, R *a0, R *a1, R *a2, R *b1, R *b2);
void beqAllPassCoef(R sr, R freq, R rq, R *a0, R *a1, R *a2, R *b1, R *b2);
void beqBandPassCoef(R sr, R freq, R bw, R *a0, R *a1, R *a2, R *b1, R *b2);
void beqBandStopCoef(R sr, R freq, R bw, R *a0, R *a1, R *a2, R *b1, R *b2);
void beqPeakEqCoef(R sr, R freq, R rq, R db, R *a0, R *a1, R *a2, R *b1, R *b2);
void beqLowShelfCoef(R sr, R freq, R rs, R db, R *a0, R *a1, R *a2, R *b1, R *b2);
void beqHiShelfCoef(R sr, R freq, R rs, R db, R *a0, R *a1, R *a2, R *b1, R *b2);

sos beqLowPass(R sr, R freq, R rq);
sos beqHiPass(R sr, R freq, R rq);
sos beqAllPass(R sr, R freq, R rq);
sos beqBandPass(R sr, R freq, R bw);
sos beqBandStop(R sr, R freq, R bw);
sos beqPeakEq(R sr, R freq, R rq, R db);
sos beqLowShelf(R sr, R freq, R rs, R db);
sos beqHiShelf(R sr, R freq, R rs, R db);

#endif
