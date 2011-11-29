#ifndef _VECTOR_H
#define _VECTOR_H

#include "float.h"

typedef struct { f32 x, y, z;} v32;

v32 make_v32(f32 x, f32 y, f32 z);
v32 vmul(f32 s, v32 v);
v32 vadd(v32 a, v32 b);
v32 vsub(v32 a, v32 b);
f32 vdot(v32 a, v32 b);
f32 vlength(v32 v);
v32 vunitise(v32 v);

#endif
