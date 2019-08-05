#ifndef _POINT_H
#define _POINT_H

#include "float.h"

typedef struct { f32 x, y; } p32;

p32 p32_make(f32 x,f32 y);
f32 p32_dot(p32 a,p32 b);
f32 p32_length(p32 p);
f32 p32_angle(p32 p);
f32 p32_distance(p32 a, p32 b);
p32 p32_polar_to_cartesian(p32 p);
p32 p32_cartesian_to_polar(p32 p);

p32 p32_rotate(p32 p,f32 ang);
p32 p32_translateP(p32 p,p32 v);
p32 p32_scale(p32 p,p32 v);
p32 p32_uscale(p32 p,f32 s);
p32 p32_shear(p32 p,f32 dxdy);

#endif
