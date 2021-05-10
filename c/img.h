#ifndef _COMMON_IMG_H
#define _COMMON_IMG_H

#include "int.h"
#include "float.h"

/* w = width ; h = height ; n = pixel channels ;
   x = x (horizontal,column), y = y (vertical,row) */

i32 img_bytes(i32 w, i32 h, i32 n);
u8 *img_alloc(i32 w, i32 h, i32 n);
void img_memset(u8 *img,i32 w, i32 h, i32 n,u8 c);
void img_set_pixel(u8 *data, i32 w, i32 n, i32 x, i32 y, const u8 *pixel);
void img_get_pixel(u8 *data, i32 w, i32 n, i32 x, i32 y, u8 *pixel);
i32 signal_x_to_screen_x(f32 x, i32 width);
i32 signal_y_to_screen_y(f32 y, i32 height);
i32 normal_x_to_screen_x(f32 x, i32 width);
i32 normal_y_to_screen_y(f32 y, i32 height);

#endif
