#include <stdbool.h>
#include <png.h>

#include "int.h"
#include "img-png.h"

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
