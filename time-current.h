#ifndef _COMMON_TIME_CURRENT_H
#define _COMMON_TIME_CURRENT_H

#include <sys/time.h>

double current_time_as_utc_real(void);
struct timespec current_time_as_utc_timespec(void);
struct timeval current_time_as_utc_timeval(void);

#endif
