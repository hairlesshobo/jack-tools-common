#ifndef _COMMON_TRACE_H
#define _COMMON_TRACE_H

#include "float.h"
#include "int.h"

void trace_interpolate(const f32 *d, i32 m, f32 t, f32 z, f32 *r);
int trace_lookup(const f32 *d, i32 n, i32 m, f32 time, f32 *r);

#endif
