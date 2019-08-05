#include <math.h>
#include <stdio.h>

#include "point.h"

p32 p32_make(f32 x,f32 y)
{
    p32 r = {x,y};
    return r;
}

f32 p32_dot(p32 a,p32 b) {
    return a.x * b.x + a.y * b.y;
}

f32 p32_length(p32 p) {
    return sqrtf(p32_dot(p, p));
}

f32 p32_angle(p32 p) {
    return atan2f(p.y, p.x);
}

f32 p32_distance(p32 a, p32 b)
{
  return hypotf(b.x - a.x,b.y - a.y);
}

p32 p32_polar_to_cartesian(p32 p)
{
    return p32_make(p.x * cosf(p.y), p.x * sinf(p.y)); /* x = rho, y = theta */
}

p32 p32_cartesian_to_polar(p32 p)
{
    return p32_make(p32_length(p), p32_angle(p));
}

p32 p32_rotate(p32 p,f32 ang)
{
  f32 c = cosf(ang);
  f32 s = sinf(ang);
  p32 r = {p.x * c - p.y * s, p.y * c + p.x * s};
  return r;
}

p32 p32_translateP(p32 p,p32 v)
{
  p32 r = { v.x + p.x, v.y + p.y };
  return r;
}

p32 p32_scale(p32 p,p32 v)
{
  p32 r = { v.x * p.x, v.y * p.y };
  return r;
}

p32 p32_uscale(p32 p,f32 s)
{
  p32 v = {s,s};
  return p32_scale(p,v);
}

p32 p32_shear(p32 p,f32 dxdy)
{
  p32 r = {p.x + dxdy * p.y, p.y};
  return r;
}
