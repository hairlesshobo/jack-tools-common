#ifndef _COMMON_TAUS88_H
#define _COMMON_TAUS88_H

#include <stdint.h>
#include "int.h"
#include "float.h"

struct taus88 {
    u32 s1, s2, s3;
};

typedef struct taus88 taus88_t;

struct taus88 taus88_std = {1243598713U, 3093459404U, 1821928721U};

inline void taus88_std_init(struct taus88 *t)
{
    t->s1 = 1243598713U;
    t->s2 = 3093459404U;
    t->s3 = 1821928721U;
}

inline struct taus88 make_taus88(u32 seed)
{
  struct taus88 t;
  t.s1 = 1243598713U ^ seed; if (t.s1 <  2) t.s1 = 1243598713U;
  t.s2 = 3093459404U ^ seed; if (t.s2 <  8) t.s2 = 3093459404U;
  t.s3 = 1821928721U ^ seed; if (t.s3 < 16) t.s3 = 1821928721U;
  return t;
}

inline u32 taus88_u32(struct taus88 *t)
{
  t->s1 = ((t->s1 &  -2) << 12) ^ (((t->s1 << 13) ^  t->s1) >> 19);
  t->s2 = ((t->s2 &  -8) <<  4) ^ (((t->s2 <<  2) ^  t->s2) >> 25);
  t->s3 = ((t->s3 & -16) << 17) ^ (((t->s3 <<  3) ^  t->s3) >> 11);
  return t->s1 ^ t->s2 ^ t->s3;
}

/* range = [0,1) */
inline f32 taus88_f32(struct taus88 *t)
{
  union {
      u32 i;
      f32 f ;
  } u;
  u.i = 0x3F800000 | (taus88_u32(t) >> 9);
  return u.f - 1.0;
}

#endif
