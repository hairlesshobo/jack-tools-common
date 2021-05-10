/* A plane in 'Hessian normal form' can be given by a normal (a unit
  vector perpendicular to the plane) and a scalar distance from the
  origin. */

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "vector.h"
#include "plane.h"

plane make_plane(v3 n, f32 d)
{
  plane p;
  p.n = n;
  p.d = d;
  return p;
}

f32 point_plane_distance(plane p, v3 v)
{
  return v3_dot(p.n, v) + p.d;
}

/* Determing if a point lies on, in front of or behind a plane. */

enum side half_space(plane p, v3 v)
{
  f32 d = point_plane_distance(p, v);
  if(d == 0.0) {
    return coincide;
  } else if(d > 0.0) {
    return front;
  } else if(d < 0.0) {
    return back;
  } else if(isnan(d)) {
    fprintf(stderr, "half_space: nan: %f\n", d);
    return coincide;
  } else {
    fprintf(stderr, "half_space: impossible condition: %f\n", d);
    return coincide;
   }
}

/* Returns #t iff p0 and p1 are not on the same side of plane. */

bool intersect (plane p, v3 v0, v3 v1)
{
  enum side t0 = half_space(p, v0);
  enum side t1 = half_space(p, v1);
  return t0 != t1;
}

/* Given that the line from v0 to v1 intersects the plane return the
   point at which it does so. -- NOTE: If n is zero t is NAN. */

v3 intersection(plane p, v3 v0, v3 v1)
{
  v3 r = v3_sub(v1, v0);
  f32 n = v3_dot(p.n, r);
  f32 t = -(v3_dot(p.n, v0) + p.d) / n;
  return v3_add(v0, v3_mul(t, r));
}

/*  i = unit incidence vector, n = unit surface normal, result = unit
    reflection vector */

v3 in_to_r(v3 i, v3 n)
{
  return v3_add(v3_mul(v3_dot(v3_mul(-1.0, i), n) * 2.0, n), i);
}

/*
;; (p0,p1) is a line that intersects the plane (n,d).  returns the
;; reflection of p0 about the point of intersection p*.  this is not
;; the same as the reflection of p0 about the point of intersection -
;; the magnitude of the reflected vector r is determined by the
;; magnitude of (p1 - p*) not the vector (p* - p0) i.


;; \
;;  \ /
;; --~---------------
;;    \
*/

v3 reflect(plane p, v3 v0, v3 v1)
{
  v3 v = intersection(p, v0, v1);
  v3 w = v3_unitise(v3_sub(v, v0));
  return v3_add(v, v3_mul(v3_mag(v3_sub(v1, v)), in_to_r(w, p.n)));
}
