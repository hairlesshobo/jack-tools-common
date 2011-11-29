#ifndef _PLANE_H
#define _PLANE_H

#include <stdbool.h>
#include "vector.h"

typedef struct {v32 n; f32 d;} plane;
enum side {front, back, coincide};

plane make_plane(v32 n, f32 d);
f32 point_plane_distance(plane p, v32 v);
enum side half_space(plane p, v32 v);
bool intersect (plane p, v32 v0, v32 v1);
v32 intersection(plane p, v32 v0, v32 v1);
v32 in_to_r(v32 i, v32 n);
v32 reflect(plane p, v32 v0, v32 v1);

#endif
