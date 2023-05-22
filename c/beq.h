#ifndef _COMMON_BEQ_H
#define _COMMON_BEQ_H

#define R double

void bLowPassCoef(R sr, R freq, R rq, R *a0, R *a1, R *a2, R *b1, R *b2);
void bHiPassCoef(R sr, R freq, R rq, R *a0, R *a1, R *a2, R *b1, R *b2);
void bAllPassCoef(R sr, R freq, R rq, R *a0, R *a1, R *a2, R *b1, R *b2);
void bBandPassCoef(R sr, R freq, R bw, R *a0, R *a1, R *a2, R *b1, R *b2);
void bBandStopCoef(R sr, R freq, R bw, R *a0, R *a1, R *a2, R *b1, R *b2);
void bPeakEqCoef(R sr, R freq, R rq, R db, R *a0, R *a1, R *a2, R *b1, R *b2);
void bLowShelfCoef(R sr, R freq, R rs, R db, R *a0, R *a1, R *a2, R *b1, R *b2);
void bHiShelfCoef(R sr, R freq, R rs, R db, R *a0, R *a1, R *a2, R *b1, R *b2);

typedef struct {R a0, a1, a2, b1, b2;} beq;

beq beqLowPass(R sr, R freq, R rq);
beq beqHiPass(R sr, R freq, R rq);
beq beqAllPass(R sr, R freq, R rq);
beq beqBandPass(R sr, R freq, R bw);
beq beqBandStop(R sr, R freq, R bw);
beq beqPeakEq(R sr, R freq, R rq, R db);
beq beqLowShelf(R sr, R freq, R rs, R db);
beq beqHiShelf(R sr, R freq, R rs, R db);

#endif
