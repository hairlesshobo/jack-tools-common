#include <stdlib.h>

#include "float.h"
#include "taus88.h"
#include "rand.h"
#include "rgba.h"
#include "vector.h"

static taus88_t taus88_std = {1243598713U, 3093459404U, 1821928721U};

f32 randf32(f32 l, f32 r)
{
  f32 n = taus88f32(&taus88_std);
  return (n * (r - l)) + l;
}

v32 randv32(f32 l, f32 r)
{
  v32 v;
  v.x = randf32(l,r);
  v.y = randf32(l,r);
  v.z = randf32(l,r);
  return v;
}

rgba randc32(f32 l, f32 r)
{
  rgba c;
  c.r = randf32(l,r);
  c.g = randf32(l,r);
  c.b = randf32(l,r);
  c.a = randf32(l,r);
  return c;
}
