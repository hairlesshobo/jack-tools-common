#ifndef _VECTOR_H
#define _VECTOR_H

#include "float.h"

typedef struct {
	f32 x, y, z;
} v3;

v3 v3_make(f32 x, f32 y, f32 z);
v3 v3_mul(f32 s, v3 v);
v3 v3_add(v3 a, v3 b);
v3 v3_sub(v3 a, v3 b);
f32 v3_dot(v3 a, v3 b);
f32 v3_mag_sq(v3 v);
f32 v3_mag(v3 v);
v3 v3_unitise(v3 v);
f32 v3_distance(v3 v1, v3 v2);

#endif
