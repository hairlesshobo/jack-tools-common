#ifndef _COMMON_COLOUR_H
#define _COMMON_COLOUR_H

#include "float.h"
#include "int.h"

void rgb_mul(u8 *c,f32 n);
u8 cga_16_rgb_colours[16][3];
u8 ega_rgb_colours[64][3];
void ega_rgb_lookup_i32(i32 ix,u8 *c);
void ega_rgb_lookup_f32(f32 n,u8 *c);

#endif
