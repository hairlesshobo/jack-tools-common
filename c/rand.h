#ifndef _COMMON_RAND_H
#define _COMMON_RAND_H

#include <stdlib.h>

#include "colour-rgba.h"
#include "float.h"
#include "taus88.h"
#include "vector.h"

taus88_t taus88_std = {1243598713U, 3093459404U, 1821928721U};

inline f32 rand_f32_st(taus88_t *st, f32 l, f32 r)
{
  f32 n = taus88f32(st);
  return (n * (r - l)) + l;
}

inline f32 rand_f32(f32 l, f32 r)
{
  return rand_f32_st(&taus88_std, l, r);
}

inline v3 rand_v3(f32 l, f32 r)
{
  v3 v;
  v.x = rand_f32(l,r);
  v.y = rand_f32(l,r);
  v.z = rand_f32(l,r);
  return v;
}

inline rgba rand_rgba(f32 l, f32 r)
{
  rgba c;
  c.r = rand_f32(l,r);
  c.g = rand_f32(l,r);
  c.b = rand_f32(l,r);
  c.a = rand_f32(l,r);
  return c;
}

#endif
