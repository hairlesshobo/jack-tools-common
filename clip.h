#ifndef _COMMON_CLIP_H
#define _COMMON_CLIP_H

#include "int.h"
#include "float.h"
#include "vector.h"

i32 clipi32(i32 n, i32 l, i32 r);
f32 clipf32(f32 n, f32 l, f32 r);
v32 clipv32(v32 v, f32 l, f32 r);

#endif
