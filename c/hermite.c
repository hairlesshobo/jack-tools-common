#include "hermite.h"

/* 4-point, 3rd-order Hermite (x-form) */
R hermitef(R x, R y0, R y1, R y2, R y3)
{
	R c0 = y1;
	R c1 = 0.5 * (y2 - y0);
	R c2 = y0 - 2.5 * y1 + 2.0 * y2 - 0.5 * y3;
	R c3 = 1.5 * (y1 - y2) + 0.5 * (y3 - y0);
	return ((c3 * x + c2) * x + c1) * x + c0;
}
