/* https://kokkinizita.linuxaudio.org/papers/digsvfilt.pdf */

#include <math.h>

#include "svf.h"

inline void svf_calculate_c1_and_c2(float f, float q, float *c1, float *c2)
{
	float pi = 3.141592653589793;
	float w = 2.0 * tan(pi * f);
	float a = w / q;
	float b = w * w;
	*c1 = (a + b) / (1.0 + a / 2.0 + b / 4.0);
	*c2 = b / (a + b);
}
