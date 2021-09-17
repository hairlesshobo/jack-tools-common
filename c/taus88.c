/* c.f. supercollider/include/plugin_interface/SC_RGen.h */
#include <stdint.h>
#include "taus88.h"

taus88_t taus88_std_init(void)
{
    taus88_t st = {1243598713U, 3093459404U, 1821928721U};
    return(st);
}

taus88_t make_taus88(u32 seed)
{
  taus88_t t;
  t.s1 = 1243598713U ^ seed; if (t.s1 <  2) t.s1 = 1243598713U;
  t.s2 = 3093459404U ^ seed; if (t.s2 <  8) t.s2 = 3093459404U;
  t.s3 = 1821928721U ^ seed; if (t.s3 < 16) t.s3 = 1821928721U;
  return t;
}

u32 taus88u32(taus88_t *t)
{
  t->s1 = ((t->s1 &  -2) << 12) ^ (((t->s1 << 13) ^  t->s1) >> 19);
  t->s2 = ((t->s2 &  -8) <<  4) ^ (((t->s2 <<  2) ^  t->s2) >> 25);
  t->s3 = ((t->s3 & -16) << 17) ^ (((t->s3 <<  3) ^  t->s3) >> 11);
  return t->s1 ^ t->s2 ^ t->s3;
}

/* range = [0,1) */
f32 taus88f32(taus88_t *t)
{
  union {u32 i ; f32 f ;} u;
  u.i = 0x3F800000 | (taus88u32(t) >> 9);
  return u.f - 1.0;
}
