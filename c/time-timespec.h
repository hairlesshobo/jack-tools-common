#ifndef _COMMON_TIME_TIMESPEC_H
#define _COMMON_TIME_TIMESPEC_H

#include <time.h>

struct timespec usec_to_timespec(unsigned long usec);
struct timespec double_to_timespec(double d);
double timespec_to_double (struct timespec t);

#endif
