#ifndef _COMMON_CFILE_H
#define _COMMON_CFILE_H

#include "failure.h"
#include <stdint.h>
#include <stdio.h>

FILE *xfopen(const char *filename, const char *opentype);
size_t xfread(void *data, size_t size, size_t count, FILE *stream);
char *fread_byte_string(FILE *fp, int n);

#endif
