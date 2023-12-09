#ifndef _COMMON_SIGNAL_INTERPOLATE_H
#define _COMMON_SIGNAL_INTERPOLATE_H

#include <math.h>

#include "float.h"
#include "int.h"

inline f32 signal_interpolate_unsafe(const f32 *signal, i32 signal_n, f32 index)
{
	i32 index_i = (i32)floorf(index);
	f32 index_f = index - (f32)index_i;
	return (signal[index_i] * (1.0 - index_f)) + (signal[index_i + 1] * index_f);
}

inline f32 signal_interpolate_circular(const f32 *signal, i32 signal_n, f32 index)
{
	i32 index_i = (i32)floorf(index);
	f32 index_f = index - (f32)index_i;
	if (index_i == signal_n - 1) {
		return (signal[index_i] * (1.0 - index_f)) + (signal[0] * index_f);
	} else {
		return (signal[index_i] * (1.0 - index_f)) + (signal[index_i + 1] * index_f);
	}
}

inline f32 signal_interpolate_circular_safe(const f32 *signal, i32 signal_n, f32 index)
{
	if (index < 0 || index >= (f32)signal_n) {
		return 0.0;
	}
	return signal_interpolate_circular(signal, signal_n, index);
}

#endif
