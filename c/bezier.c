#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "bezier.h"
#include "print.h"

void bezier4(R x0, R y0, R x1, R y1, R x2, R y2, R x3, R y3, R mu, R *rx, R *ry)
{
	R a = 1 - mu;
	R b = a * a * a;
	R c = mu * mu * mu;
	R x = b * x0 + 3 * mu * a * a * x1 + 3 * mu * mu * a * x2 + c * x3;
	R y = b * y0 + 3 * mu * a * a * y1 + 3 * mu * mu * a * y2 + c * y3;
	assert(mu >= 0.0 && mu <= 1.0);
	assert(x0 < x3);
	*rx = x;
	*ry = y;
}

void bezier4_clip_x(R x0, R y0, R x1, R y1, R x2, R y2, R x3, R y3, R mu, R *rx, R *ry)
{
	bezier4(x0, y0, x1, y1, x2, y2, x3, y3, mu, rx, ry);
	if (*rx < x0) {
		dprintf("bezier4: x=%f < x0=%f\n", *rx, x0);
		*rx = x0;
	} else if (*rx > x3) {
		dprintf("bezier4: x=%f > x3=%f\n", *rx, x3);
		*rx = x3;
	}
}

R unwrap_mu(R x0, R x3, R mu)
{
	assert(mu >= x0 && mu <= x3);
	assert(x0 < x3);
	return (mu - x0) / (x3 - x0);
}

R next_mu(R x0, R x3)
{
	assert(x0 < x3);
	return x0 + ((x3 - x0) / 2);
}

R bezier4_y_mt(int halt, R dx, R x0, R y0, R x1, R y1, R x2, R y2, R x3, R y3, R x)
{
	R mu = x0 + ((x3 - x0) / 2);
	R l = x0;
	R r = x3;
	R ry = 0.0;
	for (int i = 0; i < halt; i++) {
		R mu_ = unwrap_mu(x0, x3, mu);
		R rx;
		bezier4_clip_x(x0, y0, x1, y1, x2, y2, x3, y3, mu_, &rx, &ry);
		if (fabsf(x - rx) <= dx) {
			return ry;
		}
		if (rx < x) {
			l = mu;
		} else {
			r = mu;
		}
		mu = next_mu(l, r);
	}
	dprintf("bezier4_y_mt: did not resolve in required steps: %d\n", halt);
	return ry;
}
