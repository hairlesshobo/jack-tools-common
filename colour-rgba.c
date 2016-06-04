#include "colour-rgba.h"
#include "float.h"

rgba make_rgba(f32 r, f32 g, f32 b, f32 a)
{
  rgba c;
  c.r = r;
  c.g = g;
  c.b = b;
  c.a = a;
  return c;
}
