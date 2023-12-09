#ifndef _COMMON_RAND_H
#define _COMMON_RAND_H

#include <stdlib.h>

#include "colour-rgba.h"
#include "float.h"
#include "taus88.h"
#include "vector.h"

inline f32 rand_f32(struct taus88 *st, f32 l, f32 r)
{
	f32 n = taus88_f32(st);
	return (n * (r - l)) + l;
}

inline v3 rand_v3(struct taus88 *st, f32 l, f32 r)
{
	v3 v;
	v.x = rand_f32(st, l, r);
	v.y = rand_f32(st, l, r);
	v.z = rand_f32(st, l, r);
	return v;
}

inline rgba rand_rgba(struct taus88 *st, f32 l, f32 r)
{
	rgba c;
	c.r = rand_f32(st, l, r);
	c.g = rand_f32(st, l, r);
	c.b = rand_f32(st, l, r);
	c.a = rand_f32(st, l, r);
	return c;
}

#endif
