#ifndef _COMMON_RAND_H
#define _COMMON_RAND_H

#include "colour-rgba.h"
#include "float.h"
#include "vector.h"

inline f32 rand_f32_st(taus88_t *st, f32 l, f32 r);
inline f32 rand_f32(f32 l, f32 r);
inline v3 rand_v3(f32 l, f32 r);
inline rgba rand_rgba(f32 l, f32 r);

#endif
