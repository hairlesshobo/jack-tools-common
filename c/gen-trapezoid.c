#include "gen-trapezoid.h"
#include "float.h"

/* Design a standard trapezoidal envelope.  `shape' determines the
   sustain time as a proportion of the duration, zero is a triangular
   envelope, one a rectangular envelope.  `skew' determines the
   attack/decay ratio, zero is an immediate attack and a slow decay,
   one a slow attack and an immediate decay.  */

void gen_trapezoid(f32 *s, int n, f32 gain, f32 shape, f32 skew)
{
#if DEBUG
	if (n != 8) {
		return;
	}
#endif

	/* x0,y0 */
	s[0] = 0.0;
	s[1] = 0.0;
	if (skew + 1.0 <= 1.0) {
		s[1] = gain;
	}

	/* x1,y1 */
	s[2] = skew * (1.0 - shape);
	s[3] = gain;

	/* x2,y2 */
	s[4] = shape + s[2];
	s[5] = gain;

	/* x3,y3 */
	s[6] = 1.0;
	s[7] = 0.0;
	if (skew - 1.0 >= 0.0) {
		s[7] = gain;
	}
}
