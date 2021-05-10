#include <stdio.h>
#include <string.h>
#include <math.h>

#include "failure.h"
#include "memory.h"
#include "img.h"
#include "int.h"
#include "float.h"


i32 img_bytes(i32 w, i32 h, i32 n)
{
    return w * h * n;
}

u8 *img_alloc(i32 w, i32 h, i32 n)
{
  return xmalloc(img_bytes(w,h,n));
}

void img_memset(u8 *img,i32 w, i32 h, i32 n,u8 c)
{
    xmemset(img,c,img_bytes(w,h,n));
}

/* data is in row order (ie. y/h scanlines of x/w pixels) */

/* w = width, n = channels (1 = GREY,3 = RGB, 4 = RGBA) */
i32 img_wnxy_to_offset(i32 w, i32 n, i32 x, i32 y)
{
  return ((w * y) + x) * n;
}

/* data = pixel map (row order), w = width, n = channels, x = column number, y = row number,
   pixel = GREY|RGB|RGBA (ie. n consecutive u8 values) */

void img_set_pixel(u8 *data, i32 w, i32 n, i32 x, i32 y, const u8 *pixel)
{
  i32 o = img_wnxy_to_offset(w,n,x,y);
  xmemcpy(data + o, pixel, n);
}

void img_get_pixel(u8 *data, i32 w, i32 n, i32 x, i32 y, u8 *pixel)
{
  i32 o = img_wnxy_to_offset(w,n,x,y);
  xmemcpy(pixel, data + o, n);
}

/* signal = (-1,1), screen = (0,w) & (h,0) */
i32 signal_x_to_screen_x(f32 x, i32 width)
{
  f32 xx = (x / 2.0) + 0.5;
  return floorf(xx * (f32)width);
}

i32 signal_y_to_screen_y(f32 y, i32 height)
{
  f32 yy = 1.0 - ((y / 2.0) + 0.5);
  return floorf(yy * (f32)height);
}

/* normal = (0,1), screen = (0,w) & (h,0) */
i32 normal_x_to_screen_x(f32 x, i32 width)
{
  return floorf(x * (f32)width);
}

i32 normal_y_to_screen_y(f32 y, i32 height)
{
  return floorf((1.0 - y) * (f32)height);
}
