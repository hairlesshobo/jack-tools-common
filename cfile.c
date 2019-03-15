#include <stdio.h>
#include <stdint.h>

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

char *fread_byte_string(FILE * fp, int n)
{
    char *s = (char *)xmalloc(n + 1);
    s[n] = '\0';
    xfread(s, 1, n, fp);
    return s;
}
