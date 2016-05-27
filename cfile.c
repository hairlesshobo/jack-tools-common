#include <stdio.h>
#include <stdint.h>

#include "byte-order.h"
#include "cfile.h"
#include "failure.h"
#include "memory.h"

FILE *xfopen(const char *filename, const char *opentype)
{
    FILE *fp = fopen(filename, opentype);
    if (!fp) {
	perror("fopen() failed");
	FAILURE;
    }
    return fp;
}

size_t xfread(void *data, size_t size, size_t count, FILE * stream)
{
    size_t err = fread(data, size, count, stream);
    if (err != count) {
	fprintf(stderr, "fread() failed\n");
	FAILURE;
    }
    return err;
}

#define GENERATE_NC_READ(tag)			\
tag fread_##tag ( FILE *fp )			\
{						\
  tag n;					\
  xfread(&n, 4, 1, fp);                         \
  return ntoh_##tag (n);			\
}

GENERATE_NC_READ(u16)
GENERATE_NC_READ(u32)
GENERATE_NC_READ(u64)
GENERATE_NC_READ(i16)
GENERATE_NC_READ(i32)
GENERATE_NC_READ(i64)
GENERATE_NC_READ(f32)
GENERATE_NC_READ(f64)

char *fread_byte_string(FILE * fp, int n)
{
    char *s = xmalloc(n + 1);
    s[n] = '\0';
    xfread(s, 1, n, fp);
    return s;
}
