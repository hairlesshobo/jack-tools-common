#include <math.h>
#include "float.h"
#include "segment-transfer.h"

/* Straight line interpolation (zero <= index <= one). */
f32
segment_transfer_interpolate_linear (f32 left,f32 right,f32 index)
{
  return ((index * (right - left)) + left);
}

/* Logarithmic interpolation function (zero <= index <= one).  This
   works by translating `index' into a logarithmic space and making a
   linear interpolation with the translated index.*/
f32
segment_transfer_interpolate_logarithmic (f32 left,f32 right,f32 index)
{
  return ((log10 ((index * 9) + 1.0)) * (right - left)) + left;
}

/* `data' is a pointer to a `size' samples that define a valid
   transfer function.  `x' is a normalized lookup index between zero
   and one. `size' must be a multiple of two, and `data' is
   interpreted as a series of x/y co-ordinates. `data' is searched
   left to right for two x co-ordinates that span `x', these are then
   interpolated to calculate the corresponding y value.  A single data
   point covers all possible x values. Out of range indexes are
   truncated left and right. Other cases are looked up in left to
   right order. */

#define SEGMENT_TRANSFER_X(index) (data[((index)*2)])
#define SEGMENT_TRANSFER_Y(index) (data[((index)*2)+1])

f32
segment_transfer_lookup_linear (f32 *data,int size,f32 x)
{
  int size_2 = size / 2;
  if (size_2 == 1) {
    return SEGMENT_TRANSFER_Y (0);
  } else if (x <= 0.0) {
    return SEGMENT_TRANSFER_Y (0);
  } else if (x >= 1.0) {
    return SEGMENT_TRANSFER_Y (size_2 - 1);
  } else {
    f32 x_left = SEGMENT_TRANSFER_X (0);
    f32 x_right;
    f32 z;
    int i;
    for (i = 1; i < size_2; i++) {
      x_right = SEGMENT_TRANSFER_X (i);
      if (x >= x_left && x <= x_right) {
	f32 y_left = SEGMENT_TRANSFER_Y (i - 1);
	f32 y_right = SEGMENT_TRANSFER_Y (i);
	z = (x - x_left) / (x_right - x_left);
	return segment_transfer_interpolate_linear (y_left,y_right,z);
      }
      x_left = x_right;
    }
  }
  /* If the transfer function is corrupt return zero. */
  return 0.0;
}
