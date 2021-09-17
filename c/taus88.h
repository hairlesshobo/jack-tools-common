#ifndef _COMMON_TAUS88_H
#define _COMMON_TAUS88_H

#include <stdint.h>
#include "int.h"
#include "float.h"

typedef struct {u32 s1, s2, s3;} taus88_t;

void taus88_std_init(taus88_t *t);
taus88_t make_taus88(u32 seed);
u32 taus88u32(taus88_t *t);
f32 taus88f32(taus88_t *t);

#endif
