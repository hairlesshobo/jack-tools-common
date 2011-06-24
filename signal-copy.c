#include <math.h>
#include <string.h>

#include "signal-copy.h"

void signal_copy_circular ( float *dst , const float *src , int n , int s )
{
  memcpy ( dst , src + s , ( n - s ) * sizeof(float) ) ;
  memcpy ( dst + ( n - s ) , src , s * sizeof(float) ) ;
}
