#include "signal-interpolate.h"
#include "float.h"
#include "int.h"

extern inline f32 signal_interpolate_unsafe(const f32 *signal, i32 signal_n, f32 index);
extern inline f32 signal_interpolate_circular(const f32 *signal, i32 signal_n, f32 index);
extern inline f32 signal_interpolate_circular_safe(const f32 *signal, i32 signal_n, f32 index);
