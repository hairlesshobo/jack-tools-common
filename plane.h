#ifndef _PLANE_H
#define _PLANE_H

#include <stdbool.h>
#include "vector.h"

typedef struct {v3 n; f32 d;} plane;
enum side {front, back, coincide};

plane make_plane(v3 n, f32 d);
f32 point_plane_distance(plane p, v3 v);
enum side half_space(plane p, v3 v);
bool intersect (plane p, v3 v0, v3 v1);
v3 intersection(plane p, v3 v0, v3 v1);
v3 in_to_r(v3 i, v3 n);
v3 reflect(plane p, v3 v0, v3 v1);

#endif
