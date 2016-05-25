#ifndef _COMMON_IMG_PNG_H
#define _COMMON_IMG_PNG_H

#include <stdbool.h>
#include "int.h"

bool read_png_hdr(FILE * fp, i32 * w, i32 * h, i32 * depth);
bool read_png_data(FILE * fp, i32 w, i32 h, i32 depth, u8 * data);
bool load_png_rgb8(char *fn,i32 *w, i32 *h,u8 **frm);
u8 **load_png_rgb8_seq(char **fn,i32 fn_n,i32 *w, i32 *h);

#endif
