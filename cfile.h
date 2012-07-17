#ifndef _COMMON_CFILE_H
#define _COMMON_CFILE_H

#include <stdio.h>
#include <stdint.h>
#include "byte-order.h"
#include "failure.h"

FILE *xfopen(const char *filename, const char *opentype);
size_t xfread(void *data, size_t size, size_t count, FILE * stream);
char *fread_byte_string(FILE * fp, int n);

u16 fread_u16(FILE *fp);
u32 fread_u32(FILE *fp);
u64 fread_u64(FILE *fp);
i16 fread_i16(FILE *fp);
i32 fread_i32(FILE *fp);
i64 fread_i64(FILE *fp);
f32 fread_f32(FILE *fp);
f64 fread_f64(FILE *fp);

#endif
