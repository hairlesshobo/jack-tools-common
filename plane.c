/* plane.c - (c) rohan drape, 2005 */

/* A plane in 'Hessian normal form' can be given by a normal (a unit
  vector perpendicular to the plane) and a scalar distance from the
  origin. */

#include <stdbool.h>
#include <math.h>
#include "vector.h"
#include "plane.h"

plane make_plane(v32 n, f32 d)
{
  plane p;
  p.n = n;
  p.d = d;
  return p;
}

f32 point_plane_distance(plane p, v32 v)
{
  return vdot(p.n, v) + p.d;
}

/* Determing if a point lies on, in front of or behind a plane. */

enum side half_space(plane p, v32 v)
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

bool intersect (plane p, v32 v0, v32 v1)
{
  enum side t0 = half_space(p, v0);
  enum side t1 = half_space(p, v1);
  return t0 != t1;
}

/* Given that the line from v0 to v1 intersects the plane return the
   point at which it does so. -- NOTE: If n is zero t is NAN. */

v32 intersection(plane p, v32 v0, v32 v1)
{
  v32 r = vsub(v1, v0);
  f32 n = vdot(p.n, r);
  f32 t = -(vdot(p.n, v0) + p.d) / n;
  return vadd(v0, vmul(t, r));
}

/*  i = unit incidence vector, n = unit surface normal, result = unit
    reflection vector */

v32 in_to_r(v32 i, v32 n)
{
  return vadd(vmul(vdot(vmul(-1.0, i), n) * 2.0, n), i);
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

v32 reflect(plane p, v32 v0, v32 v1)
{
  v32 v = intersection(p, v0, v1);
  v32 w = vunitise(vsub(v, v0));
  return vadd(v, vmul(vlength(vsub(v1, v)), in_to_r(w, p.n)));
}
