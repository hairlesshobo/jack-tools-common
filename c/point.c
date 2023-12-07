#include <math.h>
#include <stdio.h>

#include "point.h"

p2 p2_make(f32 x, f32 y)
{
	return (p2) { x, y };
}

f32 p2_dot(p2 a, p2 b)
{
	return a.x * b.x + a.y * b.y;
}

f32 p2_mag_sq(p2 p)
{
	return (p.x * p.x + p.y * p.y);
}

/* distance from origin */
f32 p2_mag(p2 p)
{
	return hypotf(p.x, p.y); /* sqrtf(p2_mag_sq(p)) */
}

/* angle to origin */
f32 p2_angle(p2 p)
{
	return atan2f(p.y, p.x);
}

f32 p2_distance(p2 a, p2 b)
{
	return hypotf(b.x - a.x, b.y - a.y);
}

p2 p2_polar_to_cartesian(p2 p)
{
	return p2_make(p.x * cosf(p.y), p.x * sinf(p.y)); /* x = rho, y = theta */
}

p2 p2_cartesian_to_polar(p2 p)
{
	return p2_make(p2_mag(p), p2_angle(p));
}

p2 p2_rotate(p2 p, f32 ang)
{
	f32 c = cosf(ang);
	f32 s = sinf(ang);
	return p2_make(p.x * c - p.y * s, p.y * c + p.x * s);
}

p2 p2_add(p2 p, p2 v)
{
	return p2_make(v.x + p.x, v.y + p.y);
}

p2 p2_mul(p2 p, p2 v)
{
	return p2_make(v.x * p.x, v.y * p.y);
}

p2 p2_scale(p2 p, f32 m)
{
	return p2_make(p.x * m, p.y * m);
}

p2 p2_shear(p2 p, f32 dxdy)
{
	p2 r = { p.x + dxdy * p.y, p.y };
	return r;
}
