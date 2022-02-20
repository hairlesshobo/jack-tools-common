#include "int.h"
#include "float.h"
#include "signal-interpolate.h"

extern inline f32 signal_interpolate(const f32 *signal, i32 signal_n, f32 index);
extern inline f32 signal_interpolate_safe(const f32 *signal, i32 signal_n, f32 index);
