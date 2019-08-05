#ifndef _COMMON_COMPLEX_H
#define _COMMON_COMPLEX_H

#include "float.h"

typedef struct {f32 r, i;} c32;

c32 c32_add(c32 a,c32 b);
c32 c32_sub(c32 a,c32 b);
c32 c32_mul(c32 a,c32 b);
c32 c32_div(c32 a,c32 b);
f32 c32_mod(c32 a);
c32 c32_conj(c32 a);

typedef struct {f64 r,i;} c64;

c64 c64_add(c64 a,c64 b);
c64 c64_sub(c64 a,c64 b);
c64 c64_mul(c64 a,c64 b);
c64 c64_div(c64 a,c64 b);
f64 c64_mod(c64 a);
c64 c64_conj(c64 a);
c64 c64_square(c64 z);
c64 c64_cube(c64 z);

#endif
