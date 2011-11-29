#include "clip.h"
#include "int.h"
#include "float.h"
#include "vector.h"

i32 clipi32(i32 n, i32 l, i32 r)
{
  if(n < l) return l; else if(n > r) return r; return n;
}

f32 clipf32(f32 n, f32 l, f32 r)
{
  if(n < l) return l; else if(n > r) return r; return n;
}

v32 clipv32(v32 v, f32 l, f32 r)
{
  return make_v32(clipf32(v.x, l, r),
		  clipf32(v.y, l, r),
		  clipf32(v.z, l, r));
}
