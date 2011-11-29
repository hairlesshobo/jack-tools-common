#include <math.h>
#include <stdio.h>
#include "vector.h"

v32 make_v32(f32 x, f32 y, f32 z)
{
  v32 v;
  v.x = x;
  v.y = y;
  v.z = z;
  return v;
}

v32 vmul(f32 s, v32 v)
{
  v32 r = { s * v.x, s * v.y, s * v.z};
  return r;
}

v32 vadd(v32 a, v32 b)
{
  v32 v = { a.x + b.x, a.y + b.y, a.z + b.z};
  return v;
}

v32 vsub(v32 a, v32 b)
{
  v32 v = { a.x - b.x, a.y - b.y, a.z - b.z};
  return v;
}

f32 vdot(v32 a, v32 b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

f32 vlength(v32 v)
{
  return sqrtf(vdot(v, v));
}

v32 vunitise(v32 v)
{
  f32 l = vlength(v);
  if(l == 0.0) {
    fprintf(stderr, "vunitise: vlength==0\n");
    return v;
  } else {
    return vmul(1.0 / l, v);
  }
}
