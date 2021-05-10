#include <stdlib.h>

#include "colour-rgba.h"
#include "float.h"
#include "taus88.h"
#include "rand.h"
#include "vector.h"

static taus88_t taus88_std = {1243598713U, 3093459404U, 1821928721U};

f32 rand_f32(f32 l, f32 r)
{
  f32 n = taus88f32(&taus88_std);
  return (n * (r - l)) + l;
}

v3 rand_v3(f32 l, f32 r)
{
  v3 v;
  v.x = rand_f32(l,r);
  v.y = rand_f32(l,r);
  v.z = rand_f32(l,r);
  return v;
}

rgba rand_rgba(f32 l, f32 r)
{
  rgba c;
  c.r = rand_f32(l,r);
  c.g = rand_f32(l,r);
  c.b = rand_f32(l,r);
  c.a = rand_f32(l,r);
  return c;
}
