#include <sys/time.h>

#include "time-current.h"
#include "time-timespec.h"
#include "time-timeval.h"

struct timespec current_time_as_utc_timespec(void)
{
	struct timespec t;
	clock_gettime(CLOCK_REALTIME, &t);
	return t;
}

/* Get the current time as a UTC double precision value. */
double current_time_as_utc_real(void)
{
	return timespec_to_double(current_time_as_utc_timespec());
}

struct timeval current_time_as_utc_timeval(void)
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return t;
}
