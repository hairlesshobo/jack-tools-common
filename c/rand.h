#ifndef _COMMON_RAND_H
#define _COMMON_RAND_H

#include "colour-rgba.h"
#include "float.h"
#include "vector.h"

f32 rand_f32_st(taus88_t *st, f32 l, f32 r);
f32 rand_f32(f32 l, f32 r);
v3 rand_v3(f32 l, f32 r);
rgba rand_rgba(f32 l, f32 r);

#endif
