#include <stdio.h>
#include <stdint.h>

#include "byte-order.h"
#include "cfile.h"
#include "cfile-byte.h"
#include "failure.h"

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
