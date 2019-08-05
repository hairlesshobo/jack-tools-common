#include <math.h>
#include <stdio.h>
#include "vector.h"

v32 v32_make(f32 x, f32 y, f32 z)
{
  v32 v;
  v.x = x;
  v.y = y;
  v.z = z;
  return v;
}

v32 v32_mul(f32 s, v32 v)
{
  v32 r = { s * v.x, s * v.y, s * v.z};
  return r;
}

v32 v32_add(v32 a, v32 b)
{
  v32 v = { a.x + b.x, a.y + b.y, a.z + b.z};
  return v;
}

v32 v32_sub(v32 a, v32 b)
{
  v32 v = { a.x - b.x, a.y - b.y, a.z - b.z};
  return v;
}

f32 v32_dot(v32 a, v32 b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

f32 v32_length(v32 v)
{
  return sqrtf(v32_dot(v, v));
}

v32 v32_unitise(v32 v)
{
  f32 l = v32_length(v);
  if(l == 0.0) {
    fprintf(stderr, "v32_unitise: v32_length==0\n");
    return v;
  } else {
    return v32_mul(1.0 / l, v);
  }
}
