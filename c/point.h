#ifndef _POINT_H
#define _POINT_H

#include "float.h"

typedef struct {
	f32 x, y;
} p2;

p2 p2_make(f32 x, f32 y);
f32 p2_dot(p2 a, p2 b);
f32 p2_mag_sq(p2 p);
f32 p2_mag(p2 p);
f32 p2_angle(p2 p);
f32 p2_distance(p2 a, p2 b);
p2 p2_polar_to_cartesian(p2 p);
p2 p2_cartesian_to_polar(p2 p);

p2 p2_rotate(p2 p, f32 ang);
p2 p2_add(p2 p, p2 v);
p2 p2_mul(p2 p, p2 v);
p2 p2_scale(p2 p, f32 m);
p2 p2_shear(p2 p, f32 dxdy);

#endif
