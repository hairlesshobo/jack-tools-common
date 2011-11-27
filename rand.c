#include <stdlib.h>

#include "float.h"
#include "taus88.h"
#include "rand.h"

f32 randf32(f32 l, f32 r)
{
  f32 n = taus88f32(&taus88_std);
  return (n * (r - l)) + l;
}
