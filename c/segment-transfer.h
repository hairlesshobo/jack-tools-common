#ifndef _COMMON_SEGMENT_TRANSFER_H
#define _COMMON_SEGMENT_TRANSFER_H

#include "float.h"

f32 segment_transfer_interpolate_linear(f32 left, f32 right, f32 index);
f32 segment_transfer_interpolate_logarithmic(f32 left, f32 right, f32 index);
f32 segment_transfer_lookup_linear(f32 *data, int size, f32 x);

#endif
