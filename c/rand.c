#include <stdlib.h>

#include "float.h"
#include "taus88.h"
#include "rand.h"
#include "vector.h"

extern inline f32 rand_f32_st(taus88_t *st, f32 l, f32 r);
extern inline f32 rand_f32(f32 l, f32 r);
extern inline v3 rand_v3(f32 l, f32 r);
extern inline rgba rand_rgba(f32 l, f32 r);
