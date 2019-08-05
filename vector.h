#ifndef _VECTOR_H
#define _VECTOR_H

#include "float.h"

typedef struct { f32 x, y, z;} v32;

v32 v32_make(f32 x, f32 y, f32 z);
v32 v32_mul(f32 s, v32 v);
v32 v32_add(v32 a, v32 b);
v32 v32_sub(v32 a, v32 b);
f32 v32_dot(v32 a, v32 b);
f32 v32_length(v32 v);
v32 v32_unitise(v32 v);

#endif
