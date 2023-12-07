#include <math.h>
#include <string.h>

#include "memory.h"
#include "signal-copy.h"

/* dst = destination, src = source, n = elements to copy, s = src start index */
void signal_copy_circular(float *dst, const float *src, int n, int s)
{
	int d = n - s;
	xmemcpy(dst, src + s, d * sizeof(float));
	xmemcpy(dst + d, src, s * sizeof(float));
}

/*
  int d = n - s;
  for(int i = 0; i < d; i++) { dst[i] = src[s + i]; }
  for(int i = 0; i < s; i++) { dst[i + d] = src[i]; }
*/
