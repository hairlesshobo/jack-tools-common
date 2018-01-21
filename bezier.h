#ifndef _COMMON_BESSEL_H
#define _COMMON_BESSEL_H

#define R float

void bezier4(R x0, R y0, R x1, R y1, R x2, R y2, R x3, R y3, R mu, R * rx, R * ry);
R bezier4_y_mt(int halt, R dx, R x0, R y0, R x1, R y1, R x2, R y2, R x3, R y3, R x);

#endif
