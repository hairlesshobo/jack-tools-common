#include <math.h>
#include <stdio.h>
#include "vector.h"

v3 v3_make(f32 x, f32 y, f32 z)
{
  v3 v;
  v.x = x;
  v.y = y;
  v.z = z;
  return v;
}

v3 v3_mul(f32 s, v3 v)
{
  v3 r = { s * v.x, s * v.y, s * v.z};
  return r;
}

v3 v3_add(v3 a, v3 b)
{
  v3 v = { a.x + b.x, a.y + b.y, a.z + b.z};
  return v;
}

v3 v3_sub(v3 a, v3 b)
{
  v3 v = { a.x - b.x, a.y - b.y, a.z - b.z};
  return v;
}

f32 v3_dot(v3 a, v3 b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

f32 v3_length(v3 v)
{
  return sqrtf(v3_dot(v, v));
}

v3 v3_unitise(v3 v)
{
  f32 l = v3_length(v);
  if(l == 0.0) {
    fprintf(stderr, "v3_unitise: v3_length==0\n");
    return v;
  } else {
    return v3_mul(1.0 / l, v);
  }
}
