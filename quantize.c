#include <math.h>
#include "float.h"
#include "quantize.h"

/* Return the multiple of `quanta' nearest to `value'. */
f32
quantize(f32 quanta,f32 value)
{
  return quanta * roundf(value/quanta);
}
