#ifndef _COMMON_CLIP_H
#define _COMMON_CLIP_H

#include "int.h"
#include "float.h"
#include "vector.h"

#define clip_typ(n,l,r) (n < l ? l : (n > r ? r : n))

i32 clip_i32(i32 n, i32 l, i32 r);
f32 clip_f32(f32 n, f32 l, f32 r);
v32 clip_v32(v32 v, f32 l, f32 r);

#endif
