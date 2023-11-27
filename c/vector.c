#include <math.h>
#include <stdio.h>

#include "vector.h" /* c-common */

v3 v3_make(f32 x, f32 y, f32 z) {
  return (v3){x,y,z};
}

v3 v3_mul(f32 s, v3 v) {
  return v3_make(s * v.x, s * v.y, s * v.z);
}

v3 v3_add(v3 a, v3 b) {
  return v3_make(a.x + b.x, a.y + b.y, a.z + b.z);
}

v3 v3_sub(v3 a, v3 b) {
  return v3_make(a.x - b.x, a.y - b.y, a.z - b.z);
}

f32 v3_dot(v3 a, v3 b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

f32 f32_squared(f32 x) {
    return x * x;
}

f32 v3_distance(v3 v1, v3 v2) {
  return sqrtf(f32_squared(v2.x - v1.x) + f32_squared(v2.y - v1.y) + f32_squared(v2.z - v1.z));
}

f32 v3_mag_sq(v3 v) {
  return v.x * v.x + v.y * v.y + v.z * v.z;
}

f32 v3_mag(v3 v) {
  return sqrtf(v3_mag_sq(v));
}

v3 v3_unitise(v3 v) {
  f32 l = v3_mag(v);
  if(l == 0.0) {
    fprintf(stderr, "v3_unitise: v3_mag==0\n");
    return v;
  } else {
    return v3_mul(1.0 / l, v);
  }
}
