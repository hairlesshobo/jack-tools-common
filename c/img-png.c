#include <stdbool.h>
#include <png.h>

#include "int.h"
#include "img-png.h"
#include "memory.h"

bool read_png_hdr(FILE * fp, i32 * w, i32 * h, i32 * depth)
{
  png_structp p = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!p) {
    return false;
  }
  png_infop info = png_create_info_struct(p);
  if (!info) {
    png_destroy_read_struct(&p, &info, NULL);
    return false;
  }
  if (setjmp(png_jmpbuf(p))) {
    png_destroy_read_struct(&p, &info, NULL);
    return false;
  } else {
    rewind(fp);
    png_init_io(p, fp);
    png_read_png(p, info, PNG_TRANSFORM_IDENTITY, NULL);
    if (PNG_COLOR_TYPE_RGB != png_get_color_type(p, info)) {
      fprintf(stderr, "non rgb\n");
      return false;
    }
    *w = png_get_image_width(p, info);
    *h = png_get_image_height(p, info);
    *depth = png_get_bit_depth(p, info);
    png_destroy_read_struct(&p, &info, NULL);
    return true;
  }
}

bool read_png_data(FILE * fp, i32 w, i32 h, i32 depth, u8 * data)
{
  png_structp p = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!p) {
    return false;
  }
  png_infop info = png_create_info_struct(p);
  if (!info) {
    png_destroy_read_struct(&p, &info, NULL);
    return false;
  }
  if (setjmp(png_jmpbuf(p))) {
    png_destroy_read_struct(&p, &info, NULL);
    return false;
  } else {
    i32 i, j, k;
    u8 **rows;
    rewind(fp);
    png_init_io(p, fp);
    png_read_png(p, info, PNG_TRANSFORM_IDENTITY, NULL);
    rows = png_get_rows(p, info);
    for (i = 0; i < h; i++) {
      for (j = 0; j < w; j++) {
        for (k = 0; k < 3; k++) {
          *data++ = rows[i][(j * 3) + k];
        }
      }
    }
    png_destroy_read_struct(&p, &info, NULL);
  }
  return true;
}

bool load_png_rgb8(char *fn,i32 *w, i32 *h,u8 **frm)
{
    FILE *fp = fopen(fn, "r");
    if (!fp) {
	fprintf(stderr,"load_png_rgb8: fopen failed\n");
	return false;
    }
    i32 depth;
    if (!read_png_hdr(fp, w, h, &depth)) {
	fprintf(stderr,"load_png_rgb8: read_png_hdr failed\n");
	return false;
    }
    if (depth != 8) {
	fprintf(stderr,"load_png_rgb8: not 8bit\n");
	return false;
    }
    i32 sz = *w * *h * 3;
    *frm = (u8 *)xmalloc(sz);
    if (!read_png_data(fp, *w, *h, depth, *frm)) {
	fprintf(stderr,"load_png_rgb8: read_png_data failed\n");
	return false;
    }
    fclose(fp);
    return true;
}

u8 **load_png_rgb8_seq(char **fn,i32 n,i32 *w, i32 *h)
{
    u8 **frm = (u8 **)xmalloc(sizeof(u8 *) * n);
    for (i32 i = 0; i < n; i++) {
        i32 width, height;
        if (!load_png_rgb8(fn[i], &width, &height, &frm[i])) {
            return NULL;
        }
        if (i == 0) {
            *w = width;
            *h = height;
        } else {
            if (*w != width || *h != height) {
                return NULL;
            }
        }
    }
    return frm;
}
