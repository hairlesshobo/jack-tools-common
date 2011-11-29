#ifndef _RGBA_H
#define _RGBA_H

#include "float.h"

typedef struct {f32 r, g, b, a;} rgba;

rgba make_rgba(f32 r, f32 g, f32 b, f32 a);

#endif
