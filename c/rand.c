#include <stdlib.h>

#include "float.h"
#include "taus88.h"
#include "rand.h"
#include "vector.h"

extern inline f32 rand_f32(taus88_t *st, f32 l, f32 r);
extern inline v3 rand_v3(taus88_t *st, f32 l, f32 r);
extern inline rgba rand_rgba(taus88_t *st, f32 l, f32 r);
