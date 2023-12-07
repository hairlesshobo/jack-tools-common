#include "colour.h"
#include "float.h"
#include "int.h"
#include "memory.h"

void rgb_mul(u8 *c, f32 n)
{
	c[0] = c[0] * n;
	c[1] = c[1] * n;
	c[2] = c[2] * n;
}

u8 cga_16_rgb_colours[16][3] = { { 0, 0, 0 }, { 0, 0, 170 }, { 0, 170, 0 }, { 0, 170, 170 },
	{ 170, 0, 0 }, { 170, 0, 170 }, { 170, 85, 0 }, { 170, 170, 170 },
	{ 85, 85, 85 }, { 85, 85, 255 }, { 85, 255, 85 }, { 85, 255, 255 },
	{ 255, 85, 85 }, { 255, 85, 255 }, { 255, 255, 85 }, { 255, 255, 255 } };

u8 ega_rgb_colours[64][3] = { { 0, 0, 0 }, { 0, 0, 170 }, { 0, 170, 0 }, { 0, 170, 170 },
	{ 170, 0, 0 }, { 170, 0, 170 }, { 170, 170, 0 }, { 170, 170, 170 },
	{ 0, 0, 85 }, { 0, 0, 255 }, { 0, 170, 85 }, { 0, 170, 255 },
	{ 170, 0, 85 }, { 170, 0, 255 }, { 170, 170, 85 }, { 170, 170, 255 },
	{ 0, 85, 0 }, { 0, 85, 170 }, { 0, 255, 0 }, { 0, 255, 170 },
	{ 170, 85, 0 }, { 170, 85, 170 }, { 170, 255, 0 }, { 170, 255, 170 },
	{ 0, 85, 85 }, { 0, 85, 255 }, { 0, 255, 85 }, { 0, 255, 255 },
	{ 170, 85, 85 }, { 170, 85, 255 }, { 170, 255, 85 }, { 170, 255, 255 },
	{ 85, 0, 0 }, { 85, 0, 170 }, { 85, 170, 0 }, { 85, 170, 170 },
	{ 255, 0, 0 }, { 255, 0, 170 }, { 255, 170, 0 }, { 255, 170, 170 },
	{ 85, 0, 85 }, { 85, 0, 255 }, { 85, 170, 85 }, { 85, 170, 255 },
	{ 255, 0, 85 }, { 255, 0, 255 }, { 255, 170, 85 }, { 255, 170, 255 },
	{ 85, 85, 0 }, { 85, 85, 170 }, { 85, 255, 0 }, { 85, 255, 170 },
	{ 255, 85, 0 }, { 255, 85, 170 }, { 255, 255, 0 }, { 255, 255, 170 },
	{ 85, 85, 85 }, { 85, 85, 255 }, { 85, 255, 85 }, { 85, 255, 255 },
	{ 255, 85, 85 }, { 255, 85, 255 }, { 255, 255, 85 }, { 255, 255, 255 } };

void ega_rgb_lookup_i32(i32 ix, u8 *c)
{
	xmemcpy(c, ega_rgb_colours[ix], 3);
}

/* n is in (0.0,1.0) */
void ega_rgb_lookup_f32(f32 n, u8 *c)
{
	i32 ix = i32_min(n * 64, 64);
	xmemcpy(c, ega_rgb_colours[ix], 3);
}
