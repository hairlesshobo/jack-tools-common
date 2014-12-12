#include <math.h>
#include <string.h>

#include "signal-copy.h"

void signal_copy_circular ( float *dst , const float *src , int n , int s )
{
  memcpy ( dst , src + s , ( n - s ) * sizeof(float) ) ;
  memcpy ( dst + ( n - s ) , src , s * sizeof(float) ) ;
}

/*
  int d = n - s;
  for(int i = 0; i < d; i++) { dst[i] = src[s + i]; }
  for(int i = 0; i < s; i++) { dst[i + d] = src[i]; }
*/
