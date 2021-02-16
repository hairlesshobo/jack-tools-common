#include "clip.h"
#include "int.h"
#include "float.h"
#include "vector.h"

i32 clip_i32(i32 n, i32 l, i32 r)
{
    return clip_typ(n,l,r);
}

f32 clip_f32(f32 n, f32 l, f32 r)
{
    return clip_typ(n,l,r);
}

v3 clip_v3(v3 v, f32 l, f32 r)
{
    return v3_make(clip_f32(v.x, l, r),
                   clip_f32(v.y, l, r),
                   clip_f32(v.z, l, r));
}
