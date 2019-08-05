#include <math.h>

#include "float.h"
#include "complex.h"

/* c32 */

c32 c32_add(c32 a, c32 b)
{
  c32 c = {a.r + b.r, a.i + b.i};
  return c;
}

c32 c32_sub(c32 a, c32 b)
{
  c32 c = {a.r - b.r, a.i - b.i};
  return c;
}

c32 c32_mul(c32 a, c32 b)
{
  c32 c = {(a.r * b.r) - (a.i * b.i), (a.r * b.i) + (a.i * b.r)};
  return c;
}

c32 c32_div(c32 a, c32 b)
{
  f32 e = b.r * b.r + b.i * b.i;
  c32 c = { (a.r * b.r + a.i * b.i) / e, (a.i * b.r - a.r * b.i) / e};
  return c;
}

f32 c32_mod(c32 a)
{
  return sqrt(a.r * a.r + a.i * a.i);
}

c32 c32_conj(c32 a)
{
  c32 c = {a.r, -a.i};
  return c;
}

/* c64 */

c64 c64_add(c64 a, c64 b)
{
  c64 c = {a.r + b.r, a.i + b.i};
  return c;
}

c64 c64_sub(c64 a, c64 b)
{
  c64 c = {a.r - b.r, a.i - b.i};
  return c;
}

c64 c64_mul(c64 a, c64 b)
{
  c64 c = {(a.r * b.r) - (a.i * b.i), (a.r * b.i) + (a.i * b.r)};
  return c;
}

c64 c64_div(c64 a, c64 b)
{
  f64 e = b.r * b.r + b.i * b.i;
  c64 c = { (a.r * b.r + a.i * b.i) / e, (a.i * b.r - a.r * b.i) / e};
  return c;
}

f64 c64_mod(c64 a)
{
  return sqrt(a.r * a.r + a.i * a.i);
}

c64 c64_conj(c64 a)
{
  c64 c = {a.r, -a.i};
  return c;
}

c64 c64_square(c64 z)
{
  return c64_mul(z,z);
}

c64 c64_cube(c64 z)
{
  return c64_mul(z,c64_square(z));
}

c64 c64_one = {1.0, 0.0};
