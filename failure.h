#ifndef _COMMON_FAILURE_H
#define _COMMON_FAILURE_H

#include <stdlib.h>

#ifndef FAILURE
#define FAILURE exit(1)
#endif

#define die(msg) fprintf(stderr,msg); FAILURE;

#endif
