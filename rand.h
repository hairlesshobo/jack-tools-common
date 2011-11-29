#ifndef _COMMON_RAND_H
#define _COMMON_RAND_H

#include "float.h"
#include "vector.h"
#include "rgba.h"

f32 randf32(f32 l, f32 r);
v32 randv32(f32 l, f32 r);
rgba randc32(f32 l, f32 r);

#endif
