#include <math.h>
#include <stdlib.h>

#include "time-timespec.h"

struct timespec usec_to_timespec(unsigned long usec)
{
  struct timespec t;
  long nsec = usec * 1000;
  ldiv_t d = ldiv(nsec, 1000000000L);
  t.tv_sec = d.quot;
  t.tv_nsec = d.rem;
  return t;
}

struct timespec double_to_timespec(double d)
{
  struct timespec t;
  double sec = floor(d);
  double nsec = (d - sec) * 1e9;
  t.tv_sec = (time_t) sec;
  t.tv_nsec = (long) nsec;
  return t;
}

double timespec_to_double (struct timespec t)
{
  return t.tv_sec + t.tv_nsec / 1e9;
}
